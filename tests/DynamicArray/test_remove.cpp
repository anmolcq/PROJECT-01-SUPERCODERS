#include <gtest/gtest.h>
#include "DynamicArray.hpp"

class DynamicArrayRemoveTest : public ::testing::Test
{
protected:
    DynamicArray<int> arr;

    void SetUp() override
    {
        for(int i=1;i<=5;i++)
            arr.append(i);
    }
};

TEST_F(DynamicArrayRemoveTest, RemoveBeginning)
{
    EXPECT_TRUE(arr.remove(0));

    EXPECT_EQ(arr.getSize(),4);
    EXPECT_EQ(arr[0],2);
}

TEST_F(DynamicArrayRemoveTest, RemoveMiddle)
{
    EXPECT_TRUE(arr.remove(2));

    EXPECT_EQ(arr[2],4);
}

TEST_F(DynamicArrayRemoveTest, RemoveEnd)
{
    EXPECT_TRUE(arr.remove(4));

    EXPECT_EQ(arr.getSize(),4);
}

TEST(DynamicArrayRemoveStandalone, InvalidIndex)
{
    DynamicArray<int> arr;

    EXPECT_FALSE(arr.remove(0));
} 