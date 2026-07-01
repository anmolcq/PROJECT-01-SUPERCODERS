#include <gtest/gtest.h>
#include "DynamicArray.hpp"

class DynamicArrayPopBackTest : public ::testing::Test
{
protected:
    DynamicArray<int> arr;

    void SetUp() override
    {
        for(int i=1;i<=5;i++)
            arr.append(i);
    }
};

TEST_F(DynamicArrayPopBackTest, PopOne)
{
    EXPECT_TRUE(arr.pop_back());

    EXPECT_EQ(arr.getSize(),4);
}

TEST_F(DynamicArrayPopBackTest, PopUntilEmpty)
{
    while(!arr.empty())
        arr.pop_back();

    EXPECT_TRUE(arr.empty());
}

TEST(DynamicArrayPopBackStandalone, PopEmpty)
{
    DynamicArray<int> arr;

    EXPECT_FALSE(arr.pop_back());
}