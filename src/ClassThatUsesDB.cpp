#include "ClassThatUsesDB.h"

//////////////////////////////////////////////////////////////////////////
/// ClassThatUsesDB metods
//////////////////////////////////////////////////////////////////////////

bool ClassThatUsesDB::openConnection(DBconnectionInterface& connector, const std::string& config)
{
    return connector.open(config);
}

bool ClassThatUsesDB::useConnection(DBconnectionInterface& connector, const std::string& execQuery)
{
    return connector.execQuery(execQuery);
}

void ClassThatUsesDB::closeConnection(DBconnectionInterface& connector)
{
    connector.close();
}

//////////////////////////////////////////////////////////////////////////
/// TestSuite1
//////////////////////////////////////////////////////////////////////////

class TestSuite1 : public ::testing::Test
{
protected:
   void SetUp()
   {
       db_user = new ClassThatUsesDB();
       mdb_connection = new MockDBconnection();
   }

   void TearDown()
   {
       delete db_user;
       delete mdb_connection;
   }

protected:
    ClassThatUsesDB* db_user;
    MockDBconnection* mdb_connection;
};

TEST_F(TestSuite1, open)
{
    EXPECT_CALL(*mdb_connection, open).WillOnce(::testing::Return(true));
    db_user->openConnection(*mdb_connection, "good config");
}

TEST_F(TestSuite1, close)
{
    EXPECT_CALL(*mdb_connection, execQuery).WillOnce(::testing::Return(true));
    db_user->useConnection(*mdb_connection,  "good command");
}

//////////////////////////////////////////////////////////////////////////
/// TestSuite2
//////////////////////////////////////////////////////////////////////////

class TestSuite2 : public ::testing::Test
{
protected:
    void SetUp()
    {
        db_user = new ClassThatUsesDB();
        db_connection = new DBConnection();
    }

    void TearDown()
    {
        delete db_user;
        delete db_connection;
    }

protected:
    ClassThatUsesDB* db_user;
    DBConnection* db_connection;
};


//
// openConnection tests 
//
TEST_F(TestSuite2, Test_opnConn_g_g) // wait good - give good
{
    bool connection_flag;
    std::string connection_conf = "good config";

    connection_flag = db_user->openConnection(*db_connection, connection_conf);

    ASSERT_TRUE(connection_flag);
}

TEST_F(TestSuite2, Test_opnConn_g_b) // wait good - give bad
{
    bool connection_flag;
    std::string connection_conf = "bad config";

    connection_flag = db_user->openConnection(*db_connection, connection_conf);

    ASSERT_TRUE(connection_flag);
}

TEST_F(TestSuite2, Test_opnConn_b_g) // wait bad - give good
{
    bool connection_flag;
    std::string connection_conf = "good config";

    connection_flag = db_user->openConnection(*db_connection, connection_conf);

    ASSERT_TRUE(!connection_flag);
}

TEST_F(TestSuite2, Test_opnConn_b_b) // wait bad - give bad
{
    bool connection_flag;
    std::string connection_conf = "bad config";

    connection_flag = db_user->openConnection(*db_connection, connection_conf);

    ASSERT_TRUE(!connection_flag);
}

//
// useConnection tests 
//
TEST_F(TestSuite2, Test_useConn_Open_g_g) // pass
{
    bool command_flag;
    std::string command = "good command";

    db_user->openConnection(*db_connection, "good config");
    command_flag = db_user->useConnection(*db_connection, command);
    ASSERT_TRUE(command_flag);
}

TEST_F(TestSuite2, Test_useConn_Open_g_b) // falue cuz command is bad
{
    bool command_flag;
    std::string command = "bad command";

    db_user->openConnection(*db_connection, "good config");
    command_flag = db_user->useConnection(*db_connection, command);
    ASSERT_TRUE(command_flag);
}

TEST_F(TestSuite2, Test_useConn_NO_Open_g_g) // falue cuz connection is closed
{
    bool command_flag;
    std::string command = "good command";

    command_flag = db_user->useConnection(*db_connection, command);
    ASSERT_TRUE(command_flag);
}

TEST_F(TestSuite2, Test_useConn_NO_Open_g_b) // falue cuz connection is closed
{
    bool command_flag;
    std::string command = "bad command";

    command_flag = db_user->useConnection(*db_connection, command);
    ASSERT_TRUE(command_flag);
}