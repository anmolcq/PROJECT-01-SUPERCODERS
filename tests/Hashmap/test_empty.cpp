#include <gtest/gtest.h>
#include "HashMap.hpp"

TEST(HashMapEmptyTest, NewMapIsEmpty)
{
    HashMap<int,int> map;

    EXPECT_TRUE(map.empty());
}

TEST(HashMapEmptyTest, InsertMakesMapNonEmpty)
{
    HashMap<int,int> map;

    map.insert(1,10);

    EXPECT_FALSE(map.empty());
}

TEST(HashMapEmptyTest, ClearMakesMapEmpty)
{
    HashMap<int,int> map;

    map.insert(1,10);

    map.clear();

    EXPECT_TRUE(map.empty());
}

TEST(HashMapEmptyTest, EraseLastElementMakesMapEmpty)
{
    HashMap<int,int> map;

    map.insert(1,10);

    map.erase(1);

    EXPECT_TRUE(map.empty());
}