#include <gtest/gtest.h>
#include "LinkedList.hpp"

TEST(LinkedListClear, ClearEmptyList)
{
    LinkedList<int> list;

    list.clear();

    EXPECT_TRUE(list.isEmpty());
}

TEST(LinkedListClear, ClearSingleNode)
{
    LinkedList<int> list;

    list.insertBack(1);
    list.clear();

    EXPECT_TRUE(list.isEmpty());
}

TEST(LinkedListClear, ClearMultipleNodes)
{
    LinkedList<int> list;

    for(int i=0;i<10;i++)
        list.insertBack(i);

    list.clear();

    EXPECT_TRUE(list.isEmpty());
}

TEST(LinkedListClear, ReuseAfterClear)
{
    LinkedList<int> list;

    list.insertBack(1);
    list.clear();
    list.insertBack(100);

    EXPECT_EQ(list.getHead()->data,100);
}

TEST(LinkedListClear, LargeList)
{
    LinkedList<int> list;

    for(int i=0;i<10000;i++)
        list.insertBack(i);

    list.clear();

    EXPECT_TRUE(list.isEmpty());
}