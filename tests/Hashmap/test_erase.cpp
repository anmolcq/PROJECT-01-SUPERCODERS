#include <gtest/gtest.h>
#include "HashMap.hpp"

class HashMapEraseTest : public ::testing::Test
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

TEST_F(HashMapEraseTest, EraseExistingKey)
{
    EXPECT_TRUE(map.erase(2));

    EXPECT_EQ(map.size(),2);
    EXPECT_FALSE(map.contains(2));
}

TEST_F(HashMapEraseTest, EraseMissingKey)
{
    EXPECT_FALSE(map.erase(100));

    EXPECT_EQ(map.size(),3);
}

TEST_F(HashMapEraseTest, EraseAllElements)
{
    map.erase(1);
    map.erase(2);
    map.erase(3);

    EXPECT_TRUE(map.empty());
}

TEST(HashMapEraseStandalone, EraseFromEmptyMap)
{
    HashMap<int,int> map;

    EXPECT_FALSE(map.erase(1));
}