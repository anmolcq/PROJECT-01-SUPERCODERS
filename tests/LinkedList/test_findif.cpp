#include <gtest/gtest.h>
#include "LinkedList.hpp"

TEST(LinkedListFindIf, FindExistingValue)
{
    LinkedList<int> list;

    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);

    auto node = list.findIf([](int x){ return x==2; });

    ASSERT_NE(node,nullptr);
    EXPECT_EQ(node->data,2);
}

TEST(LinkedListFindIf, FindFirstElement)
{
    LinkedList<int> list;

    list.insertBack(5);

    EXPECT_EQ(list.findIf([](int x){return x==5;})->data,5);
}

TEST(LinkedListFindIf, FindLastElement)
{
    LinkedList<int> list;

    list.insertBack(1);
    list.insertBack(9);

    EXPECT_EQ(list.findIf([](int x){return x==9;})->data,9);
}

TEST(LinkedListFindIf, ValueNotFound)
{
    LinkedList<int> list;

    list.insertBack(1);

    EXPECT_EQ(list.findIf([](int x){return x==10;}),nullptr);
}

TEST(LinkedListFindIf, EmptyList)
{
    LinkedList<int> list;

    EXPECT_EQ(list.findIf([](int){return true;}),nullptr);
}