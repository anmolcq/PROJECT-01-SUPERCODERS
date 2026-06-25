
#include <cstddef>
#include <cstring>
#include <string>
#include <type_traits>

template<typename T, typename Enable = void>
struct DefaultHasher;

//-----------------------------
// Integral Types
//-----------------------------
template<typename T>
struct DefaultHasher<T,
    typename std::enable_if<std::is_integral<T>::value>::type>
{
    size_t operator()(const T& key) const
    {
        return static_cast<size_t>(key);
    }
};


template<typename T>
struct DefaultHasher<T,
    typename std::enable_if<std::is_floating_point<T>::value>::type>
{
    size_t operator()(const T& key) const
    {
        const unsigned char* bytes =
            reinterpret_cast<const unsigned char*>(&key);

        size_t hash = 2166136261u;

        for(size_t i=0;i<sizeof(T);i++)
        {
            hash ^= bytes[i];
            hash *= 16777619u;
        }   

        return hash;
    }
};

//-----------------------------
// std::string
//-----------------------------
template<>
struct DefaultHasher<std::string>
{
    size_t operator()(const std::string& key) const
    {
        size_t hash = 5381;

        for(char c : key)
            hash = ((hash << 5) + hash) + c;

        return hash;
    }
};

//-----------------------------
// C String
//-----------------------------
template<>
struct DefaultHasher<const char*>
{
    size_t operator()(const char* key) const
    {
        size_t hash = 5381;

        while(*key)
        {
            hash=((hash<<5)+hash)+*key++;
        }

        return hash;
    }
};

template<>
struct DefaultHasher<char*>
{
    size_t operator()(const char* key) const
    {
        size_t hash=5381;

        while(*key)
        {
            hash=((hash<<5)+hash)+*key++;
        }

        return hash;
    }
};

