#include <gtest/gtest.h>
#include "RedisLite.hpp"

class RedisLiteSetTest : public ::testing::Test
{
protected:
    RedisLite redis;

    void SetUp() override
    {
        redis.set("name", "Anmol");
        redis.set("city", "Raipur");
    }
};

TEST_F(RedisLiteSetTest, InsertNewKey)
{
    redis.set("country", "India");

    EXPECT_EQ(redis.size(), 3);

    std::string value;
    EXPECT_TRUE(redis.get("country", value));
    EXPECT_EQ(value, "India");
}

TEST_F(RedisLiteSetTest, UpdateExistingKey)
{
    redis.set("name", "Aman");

    EXPECT_EQ(redis.size(), 2);

    std::string value;
    EXPECT_TRUE(redis.get("name", value));
    EXPECT_EQ(value, "Aman");
}

TEST_F(RedisLiteSetTest, InsertEmptyValue)
{
    redis.set("empty", "");

    std::string value;

    EXPECT_TRUE(redis.get("empty", value));
    EXPECT_EQ(value, "");
    EXPECT_EQ(redis.size(), 3);
}

TEST_F(RedisLiteSetTest, InsertEmptyKey)
{
    redis.set("", "BlankKey");

    std::string value;

    EXPECT_TRUE(redis.get("", value));
    EXPECT_EQ(value, "BlankKey");
    EXPECT_EQ(redis.size(), 3);
}

TEST_F(RedisLiteSetTest, InsertLongStringValue)
{
    std::string longValue(1000, 'A');

    redis.set("data", longValue);

    std::string value;

    EXPECT_TRUE(redis.get("data", value));
    EXPECT_EQ(value, longValue);
}

TEST_F(RedisLiteSetTest, MultipleInsertions)
{
    for(int i = 0; i < 100; i++)
    {
        redis.set("key" + std::to_string(i),
                  "value" + std::to_string(i));
    }

    EXPECT_EQ(redis.size(), 102);

    std::string value;

    EXPECT_TRUE(redis.get("key50", value));
    EXPECT_EQ(value, "value50");

    EXPECT_TRUE(redis.get("key99", value));
    EXPECT_EQ(value, "value99");
}

TEST(RedisLiteSetStandalone, InsertIntoEmptyDatabase)
{
    RedisLite redis;

    redis.set("fruit", "Apple");

    EXPECT_EQ(redis.size(), 1);

    std::string value;

    EXPECT_TRUE(redis.get("fruit", value));
    EXPECT_EQ(value, "Apple");
}

TEST(RedisLiteSetStandalone, OverwriteKeyMultipleTimes)
{
    RedisLite redis;

    redis.set("score", "10");
    redis.set("score", "20");
    redis.set("score", "30");

    EXPECT_EQ(redis.size(), 1);

    std::string value;

    EXPECT_TRUE(redis.get("score", value));
    EXPECT_EQ(value, "30");
}