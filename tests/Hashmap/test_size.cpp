#include <gtest/gtest.h>
#include "HashMap.hpp"

TEST(HashMapSizeTest, InitiallyZero)
{
    HashMap<int,int> map;

    EXPECT_EQ(map.size(),0);
}

TEST(HashMapSizeTest, SizeAfterInsert)
{
    HashMap<int,int> map;

    map.insert(1,10);
    map.insert(2,20);

    EXPECT_EQ(map.size(),2);
}

TEST(HashMapSizeTest, SizeAfterErase)
{
    HashMap<int,int> map;

    map.insert(1,10);
    map.insert(2,20);

    map.erase(1);

    EXPECT_EQ(map.size(),1);
}

TEST(HashMapSizeTest, DuplicateKeyDoesNotIncreaseSize)
{
    HashMap<int,int> map;

    map.insert(1,10);
    map.insert(1,20);

    EXPECT_EQ(map.size(),1);
}