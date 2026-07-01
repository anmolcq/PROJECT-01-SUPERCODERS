#include <gtest/gtest.h>
#include "LinkedList.hpp"

TEST(LinkedListIsEmpty, EmptyInitially)
{
    LinkedList<int> list;
    EXPECT_TRUE(list.isEmpty());
}

TEST(LinkedListIsEmpty, AfterInsertion)
{
    LinkedList<int> list;
    list.insertBack(1);

    EXPECT_FALSE(list.isEmpty());
}

TEST(LinkedListIsEmpty, AfterClear)
{
    LinkedList<int> list;

    list.insertBack(1);
    list.clear();

    EXPECT_TRUE(list.isEmpty());
}

TEST(LinkedListIsEmpty, AfterRemoveFront)
{
    LinkedList<int> list;

    list.insertBack(1);
    list.removeFront();

    EXPECT_TRUE(list.isEmpty());
}

TEST(LinkedListIsEmpty, AfterRemoveBack)
{
    LinkedList<int> list;

    list.insertBack(1);
    list.removeBack();

    EXPECT_TRUE(list.isEmpty());
}