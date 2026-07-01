#include <gtest/gtest.h>
#include "LinkedList.hpp"

TEST(LinkedListGetHead, EmptyList)
{
    LinkedList<int> list;

    EXPECT_EQ(list.getHead(),nullptr);
}

TEST(LinkedListGetHead, SingleNode)
{
    LinkedList<int> list;

    list.insertBack(5);

    EXPECT_EQ(list.getHead()->data,5);
}

TEST(LinkedListGetHead, MultipleNodes)
{
    LinkedList<int> list;

    list.insertBack(1);
    list.insertBack(2);

    EXPECT_EQ(list.getHead()->data,1);
}

TEST(LinkedListGetHead, AfterRemoveFront)
{
    LinkedList<int> list;

    list.insertBack(1);
    list.insertBack(2);

    list.removeFront();

    EXPECT_EQ(list.getHead()->data,2);
}

TEST(LinkedListGetHead, AfterClear)
{
    LinkedList<int> list;

    list.insertBack(1);

    list.clear();

    EXPECT_EQ(list.getHead(),nullptr);
}