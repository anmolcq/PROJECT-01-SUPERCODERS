#include <gtest/gtest.h>
#include "LinkedList.hpp"

class LinkedListInsertFrontTest : public ::testing::Test
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

TEST_F(LinkedListInsertFrontTest, InsertAtFront)
{
    list.insertFront(100);

    EXPECT_EQ(list.getSize(),4u);
    EXPECT_EQ(list.getHead()->data,100);
}

TEST_F(LinkedListInsertFrontTest, MultipleFrontInsertions)
{
    list.insertFront(10);
    list.insertFront(20);

    EXPECT_EQ(list.getSize(),5u);
    EXPECT_EQ(list.getHead()->data,20);
}

TEST(LinkedListInsertFrontStandalone, InsertIntoEmptyList)
{
    LinkedList<int> list;

    list.insertFront(5);

    EXPECT_FALSE(list.isEmpty());
    EXPECT_EQ(list.getSize(),1u);
    EXPECT_EQ(list.getHead()->data,5);
}

TEST(LinkedListInsertFrontStandalone, InsertNegativeNumber)
{
    LinkedList<int> list;

    list.insertFront(-10);

    EXPECT_EQ(list.getHead()->data,-10);
}

TEST(LinkedListInsertFrontStandalone, InsertLargeNumber)
{
    LinkedList<int> list;

    list.insertFront(100000);

    EXPECT_EQ(list.getHead()->data,100000);
}