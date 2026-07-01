#include <gtest/gtest.h>
#include "DynamicArray.hpp"

TEST(DynamicArrayEmptyTest, InitiallyEmpty)
{
    DynamicArray<int> arr;

    EXPECT_TRUE(arr.empty());
}

TEST(DynamicArrayEmptyTest, NotEmpty)
{
    DynamicArray<int> arr;

    arr.append(1);

    EXPECT_FALSE(arr.empty());
}

TEST(DynamicArrayEmptyTest, EmptyAfterPop)
{
    DynamicArray<int> arr;

    arr.append(1);
    arr.pop_back();

    EXPECT_TRUE(arr.empty());
}