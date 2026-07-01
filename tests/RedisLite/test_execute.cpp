#include <gtest/gtest.h>
#include "RedisLite.hpp"
#include "Command.hpp"

class RedisLiteExecuteTest : public ::testing::Test
{
protected:
    RedisLite redis;
    Command command;
};

TEST_F(RedisLiteExecuteTest, ExecuteSetCommand)
{
    command.type = CommandType::SET;
    command.key = "name";
    command.value = "Anmol";

    EXPECT_EQ(redis.execute(command), "OK");

    std::string value;
    EXPECT_TRUE(redis.get("name", value));
    EXPECT_EQ(value, "Anmol");
}

TEST_F(RedisLiteExecuteTest, ExecuteGetExistingKey)
{
    redis.set("city", "Raipur");

    command.type = CommandType::GET;
    command.key = "city";

    EXPECT_EQ(redis.execute(command), "Raipur");
}

TEST_F(RedisLiteExecuteTest, ExecuteGetNonExistingKey)
{
    command.type = CommandType::GET;
    command.key = "country";

    EXPECT_EQ(redis.execute(command), "(nil)");
}

TEST_F(RedisLiteExecuteTest, ExecuteDeleteExistingKey)
{
    redis.set("age", "20");

    command.type = CommandType::DEL;
    command.key = "age";

    EXPECT_EQ(redis.execute(command), "(integer) 1");
    EXPECT_FALSE(redis.exists("age"));
}

TEST_F(RedisLiteExecuteTest, ExecuteDeleteNonExistingKey)
{
    command.type = CommandType::DEL;
    command.key = "dummy";

    EXPECT_EQ(redis.execute(command), "(integer) 0");
}

TEST_F(RedisLiteExecuteTest, ExecuteExistsForExistingKey)
{
    redis.set("country", "India");

    command.type = CommandType::EXISTS;
    command.key = "country";

    EXPECT_EQ(redis.execute(command), "(integer) 1");
}

TEST_F(RedisLiteExecuteTest, ExecuteExistsForMissingKey)
{
    command.type = CommandType::EXISTS;
    command.key = "xyz";

    EXPECT_EQ(redis.execute(command), "(integer) 0");
}

TEST_F(RedisLiteExecuteTest, ExecuteSizeCommand)
{
    redis.set("A", "1");
    redis.set("B", "2");

    command.type = CommandType::SIZE;

    EXPECT_EQ(redis.execute(command), "(integer) 2");
}

TEST_F(RedisLiteExecuteTest, ExecuteClearCommand)
{
    redis.set("A", "1");
    redis.set("B", "2");

    command.type = CommandType::CLEAR;

    EXPECT_EQ(redis.execute(command), "OK");

    EXPECT_TRUE(redis.empty());
    EXPECT_EQ(redis.size(), 0);
}

TEST_F(RedisLiteExecuteTest, ExecuteExitCommand)
{
    command.type = CommandType::EXIT;

    EXPECT_EQ(redis.execute(command), "Bye!");
}

TEST_F(RedisLiteExecuteTest, ExecuteInvalidCommand)
{
    command.type = CommandType::INVALID;

    EXPECT_EQ(redis.execute(command), "ERR unknown command");
}

TEST_F(RedisLiteExecuteTest, ExecuteMultipleCommandsSequentially)
{
    command.type = CommandType::SET;
    command.key = "name";
    command.value = "Anmol";

    EXPECT_EQ(redis.execute(command), "OK");

    command.type = CommandType::GET;
    command.key = "name";

    EXPECT_EQ(redis.execute(command), "Anmol");

    command.type = CommandType::SIZE;

    EXPECT_EQ(redis.execute(command), "(integer) 1");

    command.type = CommandType::DEL;
    command.key = "name";

    EXPECT_EQ(redis.execute(command), "(integer) 1");

    command.type = CommandType::SIZE;

    EXPECT_EQ(redis.execute(command), "(integer) 0");
}

TEST_F(RedisLiteExecuteTest, ExecuteOverwriteValue)
{
    command.type = CommandType::SET;
    command.key = "language";
    command.value = "C";

    redis.execute(command);

    command.value = "C++";

    redis.execute(command);

    command.type = CommandType::GET;
    command.key = "language";

    EXPECT_EQ(redis.execute(command), "C++");
}