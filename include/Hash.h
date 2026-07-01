
#include <cstddef>

#include <string>
#include <type_traits>

template<typename T, typename Enable = void>
struct DefaultHasher;
//-----------------------------
// Hash Combine
//-----------------------------
inline void hashCombine(size_t& seed,size_t hash)
{
    seed = seed*31 +hash;
}
//-----------------------------
// Combine Value
//-----------------------------
template<typename T, typename Hasher=DefaultHasher<T>>
inline void combineValue(size_t& seed,const T& value)
{
    hashCombine(seed,Hasher()(value));
}
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

// For float which converts to int.
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
//-----------------------------
// User-defined objects
//-----------------------------
 template<typename T>
struct DefaultHasher<T,
    typename std::enable_if<std::is_class<T>::value>::type>
    {
        size_t operator()(const T& obj) const
        {
            size_t seed =0;
            obj.hashFields(seed);
            return seed;                        
        }
    };

