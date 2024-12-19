#include "DBconnection.h"

//////////////////////////////////////////////////////////////////////////
/// DBConnection metods
//////////////////////////////////////////////////////////////////////////

bool DBConnection::open(const std::string& config)
{
    if(config == "good config")
    {
        this->is_active = true;
        return true;
    }    
    else
        return false;
}

void DBConnection::close()
{
    this->is_active = false;
}

bool DBConnection::execQuery(const std::string& command)
{
    if(!is_active)
        return false;

    if(command == "good command")
        return true;
    else
        return false;
}

//////////////////////////////////////////////////////////////////////////
/// TESTS
//////////////////////////////////////////////////////////////////////////

void connectAndDoSomthing(DBconnectionInterface* db_conn, const std::string& config)
{
    std::string command = "good command";

    db_conn->open(config);

    db_conn->execQuery(command);
    db_conn->execQuery(command);
    db_conn->execQuery(command);

    db_conn->close();
}

TEST(MockDBconnection, test1)
{
    ::testing::NaggyMock<MockDBconnection> MockDBconnection;
    std::string config = "good config";


    // указываем «ожидания» по использованию — методы будут вызваны хотя бы N раз
    EXPECT_CALL(MockDBconnection, execQuery).Times(::testing::AtLeast(2));

    //указываем «ожидания» по использованию — методы будут вызваны точно N раз
    EXPECT_CALL(MockDBconnection, open).Times(1);
    EXPECT_CALL(MockDBconnection, close).Times(1);


    // запускаем алгоритм на выполнение
    connectAndDoSomthing(&MockDBconnection, config);
}

TEST(MockDBconnection, test2)
{
    ::testing::StrictMock<MockDBconnection> MockDBconnection;
    std::string config = "good config";


    // указываем «ожидания» по использованию — методы будут вызваны хотя бы N раз
    EXPECT_CALL(MockDBconnection, execQuery).Times(2);

    //указываем «ожидания» по использованию — методы будут вызваны точно N раз
    EXPECT_CALL(MockDBconnection, open).Times(1);
    EXPECT_CALL(MockDBconnection, close).Times(1);


    // запускаем алгоритм на выполнение
    connectAndDoSomthing(&MockDBconnection, config);
}