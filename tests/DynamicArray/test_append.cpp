#include <gtest/gtest.h>

#include "DynamicArray.hpp"

class DynamicArrayAppendTest : public ::testing::Test
{
protected:
    DynamicArray<int> arr;
};

TEST_F(DynamicArrayAppendTest, AppendSingleElement)
{
    arr.append(10);

    EXPECT_EQ(arr.getSize(),1);
    EXPECT_EQ(arr[0],10);
}

TEST_F(DynamicArrayAppendTest, AppendMultipleElements)
{
    for(int i=1;i<=5;i++)
        arr.append(i);

    EXPECT_EQ(arr.getSize(),5);

    for(int i=0;i<5;i++)
        EXPECT_EQ(arr[i],i+1);
}

TEST_F(DynamicArrayAppendTest, AppendTriggersGrow)
{
    for(int i=0;i<5;i++)
        arr.append(i);

    EXPECT_EQ(arr.getCapacity(),8);
}