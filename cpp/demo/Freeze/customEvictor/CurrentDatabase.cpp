// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Freeze/Freeze.h>
#include <CurrentDatabase.h>

using namespace std;
using namespace IceUtil;

//
// This implementation is very simple but not restartable, i.e., you
// can only create and destroy one CurrentDatabase per process run.
//

#if defined(_MSC_VER) || defined(__BCPLUSPLUS__)
   #define __thread __declspec(thread)
#endif

namespace
{

#ifdef __HP_aCC
//
// Strange HP aCC (or linker) bug, so we use directly the pthread calls
//
pthread_key_t dbKey;
#else
__thread Database* db = 0;
#endif

}

CurrentDatabase::CurrentDatabase(const Ice::CommunicatorPtr& comm, const string& envName, const string& dbName) :
    _communicator(comm),
    _envName(envName),
    _dbName(dbName)
{
#ifdef __HP_aCC
    int rs = pthread_key_create(&dbKey, 0);
    assert(rs == 0);
#endif
}

CurrentDatabase::~CurrentDatabase()
{
    for(list<Database*>::iterator p = _dbList.begin(); p != _dbList.end(); ++p)
    {
        delete *p;
    }
}

Database&
CurrentDatabase::get()
{
#ifdef __HP_aCC
    Database* db = static_cast<Database*>(pthread_getspecific(dbKey));
#endif

    if(db == 0)
    {
        Freeze::ConnectionPtr connection = Freeze::createConnection(_communicator, _envName);
        db = new Database(connection, _dbName);

        Mutex::Lock sync(_dbListMutex);
        _dbList.push_back(db);
#ifdef __HP_aCC
	int rs = pthread_setspecific(dbKey, db);
	assert(rs == 0);
#endif
    }
    return *db;
}
