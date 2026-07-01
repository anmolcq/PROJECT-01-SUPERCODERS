#include <gtest/gtest.h>
#include "CommandParser.hpp"

class CommandParserParseTest : public ::testing::Test
{
protected:
    CommandParser parser;
};

TEST_F(CommandParserParseTest, ParseSetCommand)
{
    Command command = parser.parse("SET name Anmol");

    EXPECT_EQ(command.type, CommandType::SET);
    EXPECT_EQ(command.key, "name");
    EXPECT_EQ(command.value, "Anmol");
}

TEST_F(CommandParserParseTest, ParseGetCommand)
{
    Command command = parser.parse("GET name");

    EXPECT_EQ(command.type, CommandType::GET);
    EXPECT_EQ(command.key, "name");
}

TEST_F(CommandParserParseTest, ParseDeleteCommand)
{
    Command command = parser.parse("DEL city");

    EXPECT_EQ(command.type, CommandType::DEL);
    EXPECT_EQ(command.key, "city");
}

TEST_F(CommandParserParseTest, ParseExistsCommand)
{
    Command command = parser.parse("EXISTS age");

    EXPECT_EQ(command.type, CommandType::EXISTS);
    EXPECT_EQ(command.key, "age");
}

TEST_F(CommandParserParseTest, ParseLowerCaseCommand)
{
    Command command = parser.parse("set language C++");

    EXPECT_EQ(command.type, CommandType::SET);
    EXPECT_EQ(command.key, "language");
    EXPECT_EQ(command.value, "C++");
}

TEST_F(CommandParserParseTest, ParseCommandWithMultipleWordValue)
{
    Command command = parser.parse("SET message Hello World From RedisLite");

    EXPECT_EQ(command.type, CommandType::SET);
    EXPECT_EQ(command.key, "message");
    EXPECT_EQ(command.value, "Hello World From RedisLite");
}

TEST_F(CommandParserParseTest, ParseSizeCommand)
{
    Command command = parser.parse("SIZE");

    EXPECT_EQ(command.type, CommandType::SIZE);
    EXPECT_TRUE(command.key.empty());
    EXPECT_TRUE(command.value.empty());
}

TEST_F(CommandParserParseTest, ParseClearCommand)
{
    Command command = parser.parse("CLEAR");

    EXPECT_EQ(command.type, CommandType::CLEAR);
    EXPECT_TRUE(command.key.empty());
    EXPECT_TRUE(command.value.empty());
}

TEST_F(CommandParserParseTest, ParseExitCommand)
{
    Command command = parser.parse("EXIT");

    EXPECT_EQ(command.type, CommandType::EXIT);
}

TEST_F(CommandParserParseTest, ParseInvalidCommand)
{
    Command command = parser.parse("RANDOM key value");

    EXPECT_EQ(command.type, CommandType::INVALID);
}

TEST_F(CommandParserParseTest, ParseEmptyInput)
{
    Command command = parser.parse("");

    EXPECT_EQ(command.type, CommandType::INVALID);
}

TEST_F(CommandParserParseTest, ParseCommandWithExtraSpaces)
{
    Command command = parser.parse("SET    username    Anmol");

    EXPECT_EQ(command.type, CommandType::SET);
    EXPECT_EQ(command.key, "username");
    EXPECT_EQ(command.value, "Anmol");
}

TEST_F(CommandParserParseTest, ParseSetWithoutValue)
{
    Command command = parser.parse("SET key");

    EXPECT_EQ(command.type, CommandType::SET);
    EXPECT_EQ(command.key, "key");
    EXPECT_TRUE(command.value.empty());
}

TEST_F(CommandParserParseTest, ParseGetWithoutKey)
{
    Command command = parser.parse("GET");

    EXPECT_EQ(command.type, CommandType::GET);
    EXPECT_TRUE(command.key.empty());
}