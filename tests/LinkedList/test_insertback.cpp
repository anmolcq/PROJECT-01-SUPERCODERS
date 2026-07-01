#include <gtest/gtest.h>
#include "LinkedList.hpp"

class LinkedListInsertBackTest : public ::testing::Test
{
protected:
    LinkedList<int> list;

    void SetUp() override
    {
        list.insertBack(1);
        list.insertBack(2);
        list.insertBack(3);
    }
};

TEST_F(LinkedListInsertBackTest, InsertSingleElement)
{
    list.insertBack(4);

    EXPECT_EQ(list.getSize(),4u);
}

TEST_F(LinkedListInsertBackTest, InsertMultipleElements)
{
    list.insertBack(4);
    list.insertBack(5);

    EXPECT_EQ(list.getSize(),5u);
}

TEST(LinkedListInsertBackStandalone, InsertIntoEmptyList)
{
    LinkedList<int> list;

    list.insertBack(10);

    EXPECT_EQ(list.getHead()->data,10);
    EXPECT_EQ(list.getSize(),1u);
}

TEST(LinkedListInsertBackStandalone, InsertNegativeValue)
{
    LinkedList<int> list;

    list.insertBack(-5);

    EXPECT_EQ(list.getHead()->data,-5);
}

TEST(LinkedListInsertBackStandalone, InsertManyElements)
{
    LinkedList<int> list;

    for(int i=0;i<1000;i++)
        list.insertBack(i);

    EXPECT_EQ(list.getSize(),1000u);
}