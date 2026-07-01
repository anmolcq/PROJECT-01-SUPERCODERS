#include <gtest/gtest.h>
#include "DynamicArray.hpp"

TEST(DynamicArrayConstructorTest, DefaultConstructor)
{
    DynamicArray<int> arr;

    EXPECT_EQ(arr.getSize(),0);
    EXPECT_EQ(arr.getCapacity(),4);
    EXPECT_TRUE(arr.empty());
}

TEST(DynamicArrayConstructorTest, DefaultConstructorAppend)
{
    DynamicArray<int> arr;

    arr.append(10);

    EXPECT_EQ(arr.getSize(),1);
    EXPECT_EQ(arr[0],10);
}

TEST(DynamicArrayConstructorTest, CountConstructorCreatesElements)
{
    DynamicArray<int> arr(5);

    EXPECT_EQ(arr.getSize(),5);
    EXPECT_EQ(arr.getCapacity(),5);

    for(int i=0;i<5;i++)
        EXPECT_EQ(arr[i],0);
}