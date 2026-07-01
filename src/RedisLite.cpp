#include "RedisLite.hpp"

void RedisLite::set(const std::string& key,
                    const std::string& value)
{
    database.insert(key, value);
}

bool RedisLite::get(const std::string& key,
                    std::string& value) const
{
    if (!database.contains(key))
        return false;

    value = database.at(key);

    return true;
}

bool RedisLite::del(const std::string& key)
{
    return database.erase(key);
}

bool RedisLite::exists(const std::string& key) const
{
    return database.contains(key);
}

void RedisLite::clear()
{
    database.clear();
}

size_t RedisLite::size() const
{
    return database.size();
}

bool RedisLite::empty() const
{
    return database.empty();
}
std::string RedisLite::execute(const Command& command)
{
    switch(command.type)
    {
        case CommandType::SET:
        {
            set(command.key, command.value);

            return "OK";
        }

        case CommandType::GET:
        {
            std::string value;

            if(get(command.key, value))
            {
                return value;
            }

            return "(nil)";
        }

        case CommandType::DEL:
        {
            return del(command.key)
                    ? "(integer) 1"
                    : "(integer) 0";
        }

        case CommandType::EXISTS:
        {
            return exists(command.key)
                    ? "(integer) 1"
                    : "(integer) 0";
        }

        case CommandType::SIZE:
        {
            return "(integer) " + std::to_string(size());
        }

        case CommandType::CLEAR:
        {
            clear();

            return "OK";
        }

        case CommandType::EXIT:
        {
            return "Bye!";
        }

        case CommandType::INVALID:
        {
            return "ERR unknown command";
        }
    }

    return "ERR";
}