#include <gtest/gtest.h>
#include "HashMap.hpp"

class HashMapInsertTest : public ::testing::Test
{
protected:
    HashMap<int, std::string> map;
};

TEST_F(HashMapInsertTest, InsertSingleElement)
{
    map.insert(1, "One");

    EXPECT_EQ(map.size(), 1);
    EXPECT_TRUE(map.contains(1));
    EXPECT_EQ(map.at(1), "One");
}

TEST_F(HashMapInsertTest, InsertMultipleElements)
{
    map.insert(1, "One");
    map.insert(2, "Two");
    map.insert(3, "Three");

    EXPECT_EQ(map.size(), 3);

    EXPECT_EQ(map.at(1), "One");
    EXPECT_EQ(map.at(2), "Two");
    EXPECT_EQ(map.at(3), "Three");
}

TEST_F(HashMapInsertTest, InsertDuplicateKeyUpdatesValue)
{
    map.insert(10, "Old");
    map.insert(10, "New");

    EXPECT_EQ(map.size(), 1);
    EXPECT_EQ(map.at(10), "New");
}

TEST_F(HashMapInsertTest, InsertTriggersRehash)
{
    HashMap<int,int> map(2);

    for(int i=0;i<20;i++)
        map.insert(i,i*10);

    EXPECT_EQ(map.size(),20);

    for(int i=0;i<20;i++)
        EXPECT_EQ(map.at(i),i*10);
}