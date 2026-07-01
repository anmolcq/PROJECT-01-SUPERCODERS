#include <gtest/gtest.h>
#include "LinkedList.hpp"

TEST(LinkedListGetSize, InitiallyZero)
{
    LinkedList<int> list;
    EXPECT_EQ(list.getSize(),0u);
}

TEST(LinkedListGetSize, AfterInsertion)
{
    LinkedList<int> list;

    list.insertBack(1);
    list.insertBack(2);

    EXPECT_EQ(list.getSize(),2u);
}

TEST(LinkedListGetSize, AfterRemove)
{
    LinkedList<int> list;

    list.insertBack(1);
    list.removeFront();

    EXPECT_EQ(list.getSize(),0u);
}

TEST(LinkedListGetSize, AfterClear)
{
    LinkedList<int> list;

    list.insertBack(1);
    list.insertBack(2);

    list.clear();

    EXPECT_EQ(list.getSize(),0u);
}

TEST(LinkedListGetSize, LargeDataset)
{
    LinkedList<int> list;

    for(int i=0;i<5000;i++)
        list.insertBack(i);

    EXPECT_EQ(list.getSize(),5000u);
}