#include <gtest/gtest.h>
#include "CLI.hpp"

#include <sstream>
#include <iostream>

class CLIRunTest : public ::testing::Test
{
protected:

    std::streambuf* cinBuffer;
    std::streambuf* coutBuffer;

    std::ostringstream output;

    void SetUp() override
    {
        cinBuffer = std::cin.rdbuf();
        coutBuffer = std::cout.rdbuf();
    }

    void TearDown() override
    {
        std::cin.rdbuf(cinBuffer);
        std::cout.rdbuf(coutBuffer);
    }
};

TEST_F(CLIRunTest, RunExitCommand)
{
    CLI cli;

    std::istringstream input(
        "EXIT\n"
    );

    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    cli.run();

    std::string result = output.str();

    EXPECT_NE(result.find("Bye!"), std::string::npos);
}

TEST_F(CLIRunTest, RunSetAndGetCommand)
{
    CLI cli;

    std::istringstream input(
        "SET name Anmol\n"
        "GET name\n"
        "EXIT\n"
    );

    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    cli.run();

    std::string result = output.str();

    EXPECT_NE(result.find("OK"), std::string::npos);
    EXPECT_NE(result.find("Anmol"), std::string::npos);
    EXPECT_NE(result.find("Bye!"), std::string::npos);
}

TEST_F(CLIRunTest, RunDeleteCommand)
{
    CLI cli;

    std::istringstream input(
        "SET city Raipur\n"
        "DEL city\n"
        "GET city\n"
        "EXIT\n"
    );

    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    cli.run();

    std::string result = output.str();

    EXPECT_NE(result.find("(integer) 1"), std::string::npos);
    EXPECT_NE(result.find("(nil)"), std::string::npos);
}

TEST_F(CLIRunTest, RunExistsCommand)
{
    CLI cli;

    std::istringstream input(
        "SET age 20\n"
        "EXISTS age\n"
        "EXISTS marks\n"
        "EXIT\n"
    );

    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    cli.run();

    std::string result = output.str();

    EXPECT_NE(result.find("(integer) 1"), std::string::npos);
    EXPECT_NE(result.find("(integer) 0"), std::string::npos);
}

TEST_F(CLIRunTest, RunSizeCommand)
{
    CLI cli;

    std::istringstream input(
        "SET A 1\n"
        "SET B 2\n"
        "SIZE\n"
        "EXIT\n"
    );

    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    cli.run();

    EXPECT_NE(output.str().find("(integer) 2"), std::string::npos);
}

TEST_F(CLIRunTest, RunClearCommand)
{
    CLI cli;

    std::istringstream input(
        "SET A 10\n"
        "SET B 20\n"
        "CLEAR\n"
        "SIZE\n"
        "EXIT\n"
    );

    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    cli.run();

    EXPECT_NE(output.str().find("(integer) 0"), std::string::npos);
}

TEST_F(CLIRunTest, RunInvalidCommand)
{
    CLI cli;

    std::istringstream input(
        "HELLO\n"
        "EXIT\n"
    );

    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    cli.run();

    EXPECT_NE(output.str().find("ERR unknown command"),
              std::string::npos);
}

TEST_F(CLIRunTest, RunEmptyInput)
{
    CLI cli;

    std::istringstream input(
        "\n"
        "\n"
        "EXIT\n"
    );

    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    cli.run();

    EXPECT_NE(output.str().find("Bye!"),
              std::string::npos);
}

TEST_F(CLIRunTest, RunOverwriteExistingKey)
{
    CLI cli;

    std::istringstream input(
        "SET language C\n"
        "SET language C++\n"
        "GET language\n"
        "EXIT\n"
    );

    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    cli.run();

    EXPECT_NE(output.str().find("C++"),
              std::string::npos);
}

TEST_F(CLIRunTest, RunMultipleCommands)
{
    CLI cli;

    std::istringstream input(
        "SET one 1\n"
        "SET two 2\n"
        "SET three 3\n"
        "GET one\n"
        "GET two\n"
        "GET three\n"
        "DEL two\n"
        "EXISTS two\n"
        "SIZE\n"
        "EXIT\n"
    );

    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    cli.run();

    std::string result = output.str();

    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
    EXPECT_NE(result.find("3"), std::string::npos);
    EXPECT_NE(result.find("(integer) 0"), std::string::npos);
    EXPECT_NE(result.find("(integer) 2"), std::string::npos);
}

TEST_F(CLIRunTest, RunLargeNumberOfCommands)
{
    CLI cli;

    std::stringstream input;

    for(int i = 0; i < 100; i++)
    {
        input << "SET key" << i
              << " value" << i << "\n";
    }

    input << "SIZE\n";
    input << "EXIT\n";

    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    cli.run();

    EXPECT_NE(output.str().find("(integer) 100"),
              std::string::npos);
}