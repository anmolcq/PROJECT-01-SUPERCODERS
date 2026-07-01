#include <gtest/gtest.h>
#include "DynamicArray.hpp"

TEST(DynamicArraySizeTest, InitialSize)
{
    DynamicArray<int> arr;

    EXPECT_EQ(arr.getSize(),0);
}

TEST(DynamicArraySizeTest, AfterAppend)
{
    DynamicArray<int> arr;

    arr.append(1);
    arr.append(2);

    EXPECT_EQ(arr.getSize(),2);
}

TEST(DynamicArraySizeTest, AfterRemove)
{
    DynamicArray<int> arr;

    arr.append(1);
    arr.append(2);

    arr.remove(0);

    EXPECT_EQ(arr.getSize(),1);
}