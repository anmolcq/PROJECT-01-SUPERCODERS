#include <gtest/gtest.h>
#include "LinkedList.hpp"

class LinkedListRemoveFrontTest : public ::testing::Test
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

TEST_F(LinkedListRemoveFrontTest, RemoveFirstNode)
{
    list.removeFront();

    EXPECT_EQ(list.getHead()->data,2);
    EXPECT_EQ(list.getSize(),2u);
}

TEST_F(LinkedListRemoveFrontTest, RemoveUntilEmpty)
{
    list.removeFront();
    list.removeFront();
    list.removeFront();

    EXPECT_TRUE(list.isEmpty());
}

TEST(LinkedListRemoveFrontStandalone, RemoveFromEmpty)
{
    LinkedList<int> list;

    EXPECT_FALSE(list.removeFront());
}

TEST(LinkedListRemoveFrontStandalone, RemoveSingleNode)
{
    LinkedList<int> list;

    list.insertBack(10);

    EXPECT_TRUE(list.removeFront());
    EXPECT_TRUE(list.isEmpty());
}

TEST(LinkedListRemoveFrontStandalone, RemoveLargeList)
{
    LinkedList<int> list;

    for(int i=0;i<500;i++)
        list.insertBack(i);

    for(int i=0;i<500;i++)
        EXPECT_TRUE(list.removeFront());

    EXPECT_TRUE(list.isEmpty());
}