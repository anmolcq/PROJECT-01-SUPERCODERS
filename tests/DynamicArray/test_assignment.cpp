#include <gtest/gtest.h>
#include "DynamicArray.hpp"

TEST(DynamicArrayAssignmentTest, BasicAssignment)
{
    DynamicArray<int> a;
    DynamicArray<int> b;

    for(int i=1;i<=5;i++)
        a.append(i);

    b=a;

    EXPECT_EQ(b.getSize(),5);
}

TEST(DynamicArrayAssignmentTest, SelfAssignment)
{
    DynamicArray<int> arr;

    arr.append(10);

    arr=arr;

    EXPECT_EQ(arr[0],10);
}

TEST(DynamicArrayAssignmentTest, DeepCopy)
{
    DynamicArray<int> a;
    DynamicArray<int> b;

    a.append(1);

    b=a;

    b[0]=100;

    EXPECT_EQ(a[0],1);
}