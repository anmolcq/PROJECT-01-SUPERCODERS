#include <gtest/gtest.h>
#include "HashMap.hpp"

class HashMapClearTest : public ::testing::Test
{
protected:
    HashMap<int,int> map;

    void SetUp() override
    {
        for(int i=0;i<5;i++)
            map.insert(i,i);
    }
};

TEST_F(HashMapClearTest, ClearRemovesEverything)
{
    map.clear();

    EXPECT_TRUE(map.empty());
    EXPECT_EQ(map.size(),0);
}

TEST_F(HashMapClearTest, CanInsertAfterClear)
{
    map.clear();

    map.insert(10,100);

    EXPECT_EQ(map.size(),1);
    EXPECT_EQ(map.at(10),100);
}

TEST(HashMapClearStandalone, ClearEmptyMap)
{
    HashMap<int,int> map;

    map.clear();

    EXPECT_TRUE(map.empty());
}