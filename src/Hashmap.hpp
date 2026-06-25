
#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "Hash.hpp"

#include <stdexcept>

template<
    typename Key,
    typename Value,
    typename Hasher = DefaultHasher<Key>
>
class HashMap
{
private:

    struct Entry
    {
        Key key;
        Value value;

        Entry() = default;

        Entry(const Key& k,const Value& v)
            : key(k), value(v)
        {
        }

        bool operator==(const Entry& other) const
        {
            return key==other.key;
        }
    };

    DynamicArray< LinkedList<Entry> > buckets;

    size_t bucketCount;

    size_t currentSize;

    float loadFactor;

    Hasher hasher;

private:

    size_t getBucketIndex(const Key& key) const
    {
        return hasher(key)%bucketCount;
    }

    void rehash(size_t newBucketCount)
    {
        DynamicArray< LinkedList<Entry> > newBuckets;

        for(size_t i=0;i<newBucketCount;i++)
            newBuckets.push_back(LinkedList<Entry>());

        for(size_t i=0;i<bucketCount;i++)
        {
            auto node=buckets[i].getHead();

            while(node)
            {
                Entry entry=node->data;

                size_t index=hasher(entry.key)%newBucketCount;

                newBuckets[index].push_back(entry);

                node=node->next;
            }
        }

        buckets=newBuckets;

        bucketCount=newBucketCount;
    }

public:

    HashMap(size_t initialBuckets=16)
        : bucketCount(initialBuckets),
          currentSize(0),
          loadFactor(0.75f)
    {
        for(size_t i=0;i<bucketCount;i++)
            buckets.push_back(LinkedList<Entry>());
    }

    size_t size() const
    {
        return currentSize;
    }

    bool empty() const
    {
        return currentSize==0;
    }

    void insert(const Key& key,const Value& value)
    {
        if((float)(currentSize+1)/bucketCount>loadFactor)
            rehash(bucketCount*2);

        size_t index=getBucketIndex(key);

        auto node=buckets[index].getHead();

        while(node)
        {
            if(node->data.key==key)
            {
                node->data.value=value;
                return;
            }

            node=node->next;
        }

        buckets[index].push_back(Entry(key,value));

        currentSize++;
    }

    bool contains(const Key& key) const
    {
        size_t index=getBucketIndex(key);

        auto node=buckets[index].getHead();

        while(node)
        {
            if(node->data.key==key)
                return true;

            node=node->next;
        }

        return false;
    }

    Value& at(const Key& key)
    {
        size_t index=getBucketIndex(key);

        auto node=buckets[index].getHead();

        while(node)
        {
            if(node->data.key==key)
                return node->data.value;

            node=node->next;
        }

        throw std::out_of_range("Key not found");
    }

    const Value& at(const Key& key) const
    {
        size_t index=getBucketIndex(key);

        auto node=buckets[index].getHead();

        while(node)
        {
            if(node->data.key==key)
                return node->data.value;

            node=node->next;
        }

        throw std::out_of_range("Key not found");
    }

    bool erase(const Key& key)
    {
        size_t index=getBucketIndex(key);

        bool removed=buckets[index].removeIf(
            [&](const Entry& e)
            {
                return e.key==key;
            });

        if(removed)
            currentSize--;

        return removed;
    }

    void clear()
    {
        for(size_t i=0;i<bucketCount;i++)
            buckets[i].clear();

        currentSize=0;
    }
};
