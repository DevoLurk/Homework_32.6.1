#pragma once

#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include "DBconnection.h"


class ClassThatUsesDB
{
public:
    ClassThatUsesDB() = default;
    ~ClassThatUsesDB() = default;

    bool openConnection(DBconnectionInterface& connector, const std::string& config);
    bool useConnection(DBconnectionInterface& connector, const std::string& execQuery);
    void closeConnection(DBconnectionInterface& connector);
};