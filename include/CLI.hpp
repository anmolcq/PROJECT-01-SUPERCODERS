#ifndef CLI_HPP
#define CLI_HPP

#include "RedisLite.hpp"
#include "CommandParser.hpp"

class CLI
{
private:

    RedisLite redis;
    CommandParser parser;

public:

    CLI() = default;

    void run();
};

#endif