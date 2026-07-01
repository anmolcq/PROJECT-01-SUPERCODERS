#include <gtest/gtest.h>
#include "DynamicArray.hpp"

class DynamicArrayInsertTest : public ::testing::Test
{
protected:
    DynamicArray<int> arr;

    void SetUp() override
    {
        for(int i=1;i<=5;i++)
            arr.append(i);
    }
};

TEST_F(DynamicArrayInsertTest, InsertBeginning)
{
    EXPECT_TRUE(arr.insert(0,100));

    EXPECT_EQ(arr.getSize(),6);
    EXPECT_EQ(arr[0],100);
}

TEST_F(DynamicArrayInsertTest, InsertMiddle)
{
    EXPECT_TRUE(arr.insert(2,99));

    EXPECT_EQ(arr[2],99);
}

TEST_F(DynamicArrayInsertTest, InsertEnd)
{
    EXPECT_TRUE(arr.insert(arr.getSize(),200));

    EXPECT_EQ(arr[5],200);
}

TEST(DynamicArrayInsertStandalone, InsertIntoEmptyArray)
{
    DynamicArray<int> arr;

    EXPECT_TRUE(arr.insert(0,10));

    EXPECT_EQ(arr.getSize(),1);
    EXPECT_EQ(arr[0],10);
}

TEST(DynamicArrayInsertStandalone, InvalidIndex)
{
    DynamicArray<int> arr;

    EXPECT_FALSE(arr.insert(2,10));
}

TEST(DynamicArrayInsertStandalone, InsertTriggersGrow)
{
    DynamicArray<int> arr;

    for(int i=0;i<4;i++)
        arr.append(i);

    EXPECT_EQ(arr.getCapacity(),4);

    arr.insert(2,100);

    EXPECT_EQ(arr.getCapacity(),8);
}