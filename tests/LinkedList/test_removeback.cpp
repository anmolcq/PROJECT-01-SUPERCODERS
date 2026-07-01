#include <gtest/gtest.h>
#include "LinkedList.hpp"

class LinkedListRemoveBackTest : public ::testing::Test
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

TEST_F(LinkedListRemoveBackTest, RemoveLastNode)
{
    list.removeBack();

    EXPECT_EQ(list.getSize(),2u);
}

TEST_F(LinkedListRemoveBackTest, RemoveAllNodes)
{
    list.removeBack();
    list.removeBack();
    list.removeBack();

    EXPECT_TRUE(list.isEmpty());
}

TEST(LinkedListRemoveBackStandalone, RemoveFromEmpty)
{
    LinkedList<int> list;

    EXPECT_FALSE(list.removeBack());
}

TEST(LinkedListRemoveBackStandalone, RemoveSingleNode)
{
    LinkedList<int> list;

    list.insertBack(1);

    EXPECT_TRUE(list.removeBack());
    EXPECT_TRUE(list.isEmpty());
}

TEST(LinkedListRemoveBackStandalone, RemoveLargeDataset)
{
    LinkedList<int> list;

    for(int i=0;i<1000;i++)
        list.insertBack(i);

    for(int i=0;i<1000;i++)
        EXPECT_TRUE(list.removeBack());

    EXPECT_TRUE(list.isEmpty());
}