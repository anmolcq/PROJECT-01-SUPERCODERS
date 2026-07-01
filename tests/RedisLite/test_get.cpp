#include <gtest/gtest.h>
#include "RedisLite.hpp"

class RedisLiteGetTest : public ::testing::Test
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

TEST_F(RedisLiteGetTest, GetExistingKey)
{
    std::string value;

    EXPECT_TRUE(redis.get("name", value));
    EXPECT_EQ(value, "Anmol");
}

TEST_F(RedisLiteGetTest, GetAnotherExistingKey)
{
    std::string value;

    EXPECT_TRUE(redis.get("city", value));
    EXPECT_EQ(value, "Raipur");
}

TEST_F(RedisLiteGetTest, GetNonExistingKey)
{
    std::string value = "Default";

    EXPECT_FALSE(redis.get("age", value));
    EXPECT_EQ(value, "Default");
}

TEST_F(RedisLiteGetTest, GetAfterUpdatingValue)
{
    redis.set("name", "Aman");

    std::string value;

    EXPECT_TRUE(redis.get("name", value));
    EXPECT_EQ(value, "Aman");
}

TEST_F(RedisLiteGetTest, GetEmptyValue)
{
    redis.set("empty", "");

    std::string value;

    EXPECT_TRUE(redis.get("empty", value));
    EXPECT_EQ(value, "");
}

TEST_F(RedisLiteGetTest, GetLongStringValue)
{
    std::string longValue(1000, 'X');

    redis.set("data", longValue);

    std::string value;

    EXPECT_TRUE(redis.get("data", value));
    EXPECT_EQ(value, longValue);
}

TEST(RedisLiteGetStandalone, GetFromEmptyDatabase)
{
    RedisLite redis;

    std::string value = "Nothing";

    EXPECT_FALSE(redis.get("name", value));
    EXPECT_EQ(value, "Nothing");
}

TEST(RedisLiteGetStandalone, GetAfterClear)
{
    RedisLite redis;

    redis.set("key", "value");
    redis.clear();

    std::string value = "Test";

    EXPECT_FALSE(redis.get("key", value));
    EXPECT_EQ(value, "Test");
}