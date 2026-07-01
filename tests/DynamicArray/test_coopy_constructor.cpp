#include <gtest/gtest.h>
#include "DynamicArray.hpp"

TEST(DynamicArrayCopyConstructorTest, DeepCopy)
{
    DynamicArray<int> a;

    for(int i=1;i<=5;i++)
        a.append(i);

    DynamicArray<int> b(a);

    EXPECT_EQ(b.getSize(),5);

    for(int i=0;i<5;i++)
        EXPECT_EQ(a[i],b[i]);
}

TEST(DynamicArrayCopyConstructorTest, ModifyCopy)
{
    DynamicArray<int> a;

    a.append(1);

    DynamicArray<int> b(a);

    b[0]=100;

    EXPECT_EQ(a[0],1);
}

TEST(DynamicArrayCopyConstructorTest, CopyEmpty)
{
    DynamicArray<int> a;

    DynamicArray<int> b(a);

    EXPECT_TRUE(b.empty());
}
