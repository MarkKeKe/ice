// **********************************************************************
//
// Copyright (c) 2002
// MutableRealms, Inc.
// Huntsville, AL, USA
//
// All Rights Reserved
//
// **********************************************************************

#ifndef ICE_TCP_TRANSCEIVER_H
#define ICE_TCP_TRANSCEIVER_H

#include <Ice/InstanceF.h>
#include <Ice/TraceLevelsF.h>
#include <Ice/LoggerF.h>
#include <Ice/Transceiver.h>

namespace __Ice
{

class TcpConnectorI;
class TcpAcceptorI;

class TcpTransceiverI : public TransceiverI
{
public:

    int fd();
    void close();
    void shutdown();
    void write(Buffer&, int);
    void read(Buffer&, int);
    std::string toString() const;
    
private:

    TcpTransceiverI(const TcpTransceiverI&);
    void operator=(const TcpTransceiverI&);

    TcpTransceiverI(Instance, int);
    virtual ~TcpTransceiverI();
    friend class TcpConnectorI; // May create TcpTransceiverIs
    friend class TcpAcceptorI; // May create TcpTransceiverIs

    Instance instance_;
    int fd_;
    fd_set rFdSet;
    fd_set wFdSet;
#ifndef ICE_NO_TRACE
    TraceLevels traceLevels_;
    ::Ice::Logger logger_;
#endif
};

}

#endif
