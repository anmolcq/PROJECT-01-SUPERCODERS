#include <gtest/gtest.h>
#include "DynamicArray.hpp"

TEST(DynamicArrayCapacityTest, InitialCapacity)
{
    DynamicArray<int> arr;

    EXPECT_EQ(arr.getCapacity(),4);
}

TEST(DynamicArrayCapacityTest, CapacityGrows)
{
    DynamicArray<int> arr;

    for(int i=0;i<5;i++)
        arr.append(i);

    EXPECT_EQ(arr.getCapacity(),8);
}

TEST(DynamicArrayCapacityTest, CapacityShrinks)
{
    DynamicArray<int> arr;

    for(int i=0;i<16;i++)
        arr.append(i);

    while(arr.getSize()>4)
        arr.pop_back();

    EXPECT_LT(arr.getCapacity(),16);
}