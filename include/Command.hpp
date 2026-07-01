#pragma once

#include <string>

enum class CommandType
{
    SET,
    GET,
    DEL,
    EXISTS,
    SIZE,
    CLEAR,
    EXIT,
    INVALID
};

struct Command
{
    CommandType type = CommandType::INVALID;

    std::string key;
    std::string value;
};

