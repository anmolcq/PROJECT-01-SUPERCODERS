
#include <string>

#include "command.hpp"

class CommandParser
{
public:

    CommandParser() = default;

    Command parse(const std::string& input) const;

private:

    CommandType getCommandType(const std::string& command) const;
};

