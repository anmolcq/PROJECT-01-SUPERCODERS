#include <string>
#include "HashMap.hpp"
#include "Command.hpp"

class RedisLite
{
private:

    HashMap<std::string, std::string> database;

public:
    

    RedisLite() = default;

    // Basic Commands
    void set(const std::string& key, const std::string& value);

    bool get(const std::string& key, std::string& value) const;

    bool del(const std::string& key);

    bool exists(const std::string& key) const;

    void clear();

    size_t size() const;
    bool empty() const;

    std::string execute(const Command& command);

};
