#pragma once

#include<gtest/gtest.h>
#include<gmock/gmock.h>

class DBconnectionInterface
{
public:
    DBconnectionInterface() = default;
    virtual ~DBconnectionInterface() = default;

    virtual bool open(const std::string& config) = 0;
    virtual void close() = 0;
    virtual bool execQuery(const std::string& command) = 0;
};

class DBConnection : public DBconnectionInterface
{
private:
    bool is_active = false;
public:
    DBConnection() = default;
    virtual ~DBConnection() = default;

    virtual bool open(const std::string& config) override;
    virtual void close() override;
    virtual bool execQuery(const std::string& command) override;
};

class MockDBconnection : public DBconnectionInterface 
{
public:
    MOCK_METHOD(bool, open, (const std::string& config), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(bool, execQuery, (const std::string& command), (override));
};
