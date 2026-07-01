
#include "CommandParser.hpp"

#include <algorithm>
#include <cctype>
#include <sstream>

CommandType CommandParser::getCommandType(const std::string& command) const
{
    if(command == "SET")
    {
        return CommandType::SET;
    }
    else if(command == "GET")
    {
        return CommandType::GET;
    }
    else if(command == "DEL")
    {
        return CommandType::DEL;
    }
    else if(command == "EXISTS")
    {
        return CommandType::EXISTS;
    }
    else if(command == "SIZE")
    {
        return CommandType::SIZE;
    }
    else if(command == "CLEAR")
    {
        return CommandType::CLEAR;
    }
    else if(command == "EXIT")
    {
        return CommandType::EXIT;
    }

    return CommandType::INVALID;
}

Command CommandParser::parse(const std::string& input) const
{
    Command command;

    std::istringstream stream(input);

    std::string operation;

    stream >> operation;

    std::transform(operation.begin(),
                   operation.end(),
                   operation.begin(),
                   [](unsigned char c)
                   {
                       return std::toupper(c);
                   });

    command.type = getCommandType(operation);

    switch(command.type)
    {
        case CommandType::SET:

            stream >> command.key;

            std::getline(stream, command.value);

            if(!command.value.empty() && command.value.front() == ' ')
            {
                command.value.erase(command.value.begin()); // changes been done in this line abter the test failed due to extra spaces in the value
            }

            break;

        case CommandType::GET:

        case CommandType::DEL:

        case CommandType::EXISTS:

            stream >> command.key;

            break;

        case CommandType::SIZE:

        case CommandType::CLEAR:

        case CommandType::EXIT:

            break;

        case CommandType::INVALID:

            break;
    }

    return command;
}