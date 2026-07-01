#include <gtest/gtest.h>
#include "LinkedList.hpp"

TEST(LinkedListRemoveIf, RemoveHead)
{
    LinkedList<int> list;

    list.insertBack(1);
    list.insertBack(2);

    EXPECT_TRUE(list.removeIf([](int x){return x==1;}));
}

TEST(LinkedListRemoveIf, RemoveMiddle)
{
    LinkedList<int> list;

    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);

    EXPECT_TRUE(list.removeIf([](int x){return x==2;}));
}

TEST(LinkedListRemoveIf, RemoveTail)
{
    LinkedList<int> list;

    list.insertBack(1);
    list.insertBack(2);

    EXPECT_TRUE(list.removeIf([](int x){return x==2;}));
}

TEST(LinkedListRemoveIf, ValueNotFound)
{
    LinkedList<int> list;

    list.insertBack(1);

    EXPECT_FALSE(list.removeIf([](int x){return x==100;}));
}

TEST(LinkedListRemoveIf, EmptyList)
{
    LinkedList<int> list;

    EXPECT_FALSE(list.removeIf([](int){return true;}));
}