#include <gtest/gtest.h>
#include "HashMap.hpp"

class HashMapAtTest : public ::testing::Test
{
protected:
    HashMap<int,std::string> map;

    void SetUp() override
    {
        map.insert(1,"A");
        map.insert(2,"B");
    }
};

TEST_F(HashMapAtTest, AccessExistingKey)
{
    EXPECT_EQ(map.at(1),"A");
}

TEST_F(HashMapAtTest, ModifyValueUsingAt)
{
    map.at(2)="Updated";

    EXPECT_EQ(map.at(2),"Updated");
}

TEST_F(HashMapAtTest, MissingKeyThrows)
{
    EXPECT_THROW(map.at(100),std::out_of_range);
}

TEST(HashMapAtStandalone, AccessEmptyMapThrows)
{
    HashMap<int,int> map;

    EXPECT_THROW(map.at(1),std::out_of_range);
}