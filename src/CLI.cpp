#include "CLI.hpp"

#include <iostream>

void CLI::run()
{
    std::string input;

    while(true)
    {
        std::cout << "RedisLite> ";

        std::getline(std::cin, input);

        if(input.empty())
        {
            continue;
        }

        Command command = parser.parse(input);

        std::cout << redis.execute(command) << std::endl;

        if(command.type == CommandType::EXIT)
        {
            break;
        }
    }
}