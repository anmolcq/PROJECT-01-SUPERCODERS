#include <gtest/gtest.h>
#include "DynamicArray.hpp"

class DynamicArrayGetTest : public ::testing::Test
{
protected:
    DynamicArray<int> arr;

    void SetUp() override
    {
        for(int i=1;i<=5;i++)
            arr.append(i);
    }
};

TEST_F(DynamicArrayGetTest, GetElement)
{
    EXPECT_EQ(arr.get(3),4);
}

TEST_F(DynamicArrayGetTest, ModifyThroughGet)
{
    arr.get(1)=100;

    EXPECT_EQ(arr[1],100);
}

TEST_F(DynamicArrayGetTest, InvalidIndex)
{
    EXPECT_THROW(arr.get(100),std::out_of_range);
}