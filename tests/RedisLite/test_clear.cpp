#include <gtest/gtest.h>
#include "RedisLite.hpp"

class RedisLiteClearTest : public ::testing::Test
{
protected:
    RedisLite redis;

    void SetUp() override
    {
        redis.set("name", "Anmol");
        redis.set("city", "Raipur");
        redis.set("country", "India");
    }
};

TEST_F(RedisLiteClearTest, ClearNonEmptyDatabase)
{
    redis.clear();

    EXPECT_TRUE(redis.empty());
    EXPECT_EQ(redis.size(), 0);
}

TEST_F(RedisLiteClearTest, ClearRemovesAllKeys)
{
    redis.clear();

    EXPECT_FALSE(redis.exists("name"));
    EXPECT_FALSE(redis.exists("city"));
    EXPECT_FALSE(redis.exists("country"));
}

TEST_F(RedisLiteClearTest, ClearThenInsertNewKey)
{
    redis.clear();

    redis.set("language", "C++");

    EXPECT_EQ(redis.size(), 1);
    EXPECT_TRUE(redis.exists("language"));

    std::string value;

    EXPECT_TRUE(redis.get("language", value));
    EXPECT_EQ(value, "C++");
}

TEST_F(RedisLiteClearTest, ClearCalledMultipleTimes)
{
    redis.clear();
    redis.clear();
    redis.clear();

    EXPECT_TRUE(redis.empty());
    EXPECT_EQ(redis.size(), 0);
}

TEST(RedisLiteClearStandalone, ClearEmptyDatabase)
{
    RedisLite redis;

    redis.clear();

    EXPECT_TRUE(redis.empty());
    EXPECT_EQ(redis.size(), 0);
}

TEST(RedisLiteClearStandalone, ClearLargeDatabase)
{
    RedisLite redis;

    for(int i = 0; i < 1000; i++)
    {
        redis.set("key" + std::to_string(i),
                  "value" + std::to_string(i));
    }

    EXPECT_EQ(redis.size(), 1000);

    redis.clear();

    EXPECT_TRUE(redis.empty());
    EXPECT_EQ(redis.size(), 0);

    std::string value;

    EXPECT_FALSE(redis.get("key500", value));
}

TEST(RedisLiteClearStandalone, ClearAfterSingleInsertion)
{
    RedisLite redis;

    redis.set("A", "1");

    redis.clear();

    EXPECT_TRUE(redis.empty());
    EXPECT_EQ(redis.size(), 0);
}