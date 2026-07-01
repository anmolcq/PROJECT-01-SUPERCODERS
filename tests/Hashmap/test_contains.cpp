#include <gtest/gtest.h>
#include "HashMap.hpp"

class HashMapContainsTest : public ::testing::Test
{
protected:
    HashMap<int,int> map;

    void SetUp() override
    {
        map.insert(1,10);
        map.insert(2,20);
        map.insert(3,30);
    }
};

TEST_F(HashMapContainsTest, ContainsExistingKey)
{
    EXPECT_TRUE(map.contains(2));
}

TEST_F(HashMapContainsTest, ContainsMissingKey)
{
    EXPECT_FALSE(map.contains(100));
}

TEST_F(HashMapContainsTest, ContainsAfterErase)
{
    map.erase(2);

    EXPECT_FALSE(map.contains(2));
}

TEST(HashMapContainsStandalone, EmptyMapReturnsFalse)
{
    HashMap<int,int> map;

    EXPECT_FALSE(map.contains(1));
}