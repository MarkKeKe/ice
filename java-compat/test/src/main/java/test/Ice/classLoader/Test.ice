// **********************************************************************
//
// Copyright (c) 2003-2017 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#pragma once

[["java:package:test.Ice.classLoader"]]
[["suppress-warning:deprecated"]] // For classes with operations
module Test
{

class ConcreteClass
{
    int i;
}

class AbstractClass
{
    void op();
}

exception E {}

interface Initial
{
    ConcreteClass getConcreteClass();
    AbstractClass getAbstractClass();
    void throwException() throws E;
    void shutdown();
}

}
