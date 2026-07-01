#include <gtest/gtest.h>
#include "DynamicArray.hpp"

class DynamicArrayOperatorTest : public ::testing::Test
{
protected:
    DynamicArray<int> arr;

    void SetUp() override
    {
        for(int i=1;i<=5;i++)
            arr.append(i);
    }
};

TEST_F(DynamicArrayOperatorTest, ReadElement)
{
    EXPECT_EQ(arr[0],1);
}

TEST_F(DynamicArrayOperatorTest, ModifyElement)
{
    arr[2]=100;

    EXPECT_EQ(arr[2],100);
}

TEST_F(DynamicArrayOperatorTest, InvalidIndex)
{
    EXPECT_THROW(arr[100],std::out_of_range);
}