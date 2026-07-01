#include <gtest/gtest.h>
#include "RedisLite.hpp"

class RedisLiteExistsTest : public ::testing::Test
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

TEST_F(RedisLiteExistsTest, ExistingKeyReturnsTrue)
{
    EXPECT_TRUE(redis.exists("name"));
}

TEST_F(RedisLiteExistsTest, AnotherExistingKeyReturnsTrue)
{
    EXPECT_TRUE(redis.exists("city"));
}

TEST_F(RedisLiteExistsTest, NonExistingKeyReturnsFalse)
{
    EXPECT_FALSE(redis.exists("age"));
}

TEST_F(RedisLiteExistsTest, ExistsAfterDeletion)
{
    EXPECT_TRUE(redis.del("city"));

    EXPECT_FALSE(redis.exists("city"));
}

TEST_F(RedisLiteExistsTest, ExistsAfterUpdatingValue)
{
    redis.set("name", "Aman");

    EXPECT_TRUE(redis.exists("name"));

    std::string value;
    EXPECT_TRUE(redis.get("name", value));
    EXPECT_EQ(value, "Aman");
}

TEST(RedisLiteExistsStandalone, ExistsInEmptyDatabase)
{
    RedisLite redis;

    EXPECT_FALSE(redis.exists("key"));
}

TEST(RedisLiteExistsStandalone, ExistsAfterClear)
{
    RedisLite redis;

    redis.set("username", "admin");
    redis.set("password", "1234");

    redis.clear();

    EXPECT_FALSE(redis.exists("username"));
    EXPECT_FALSE(redis.exists("password"));
    EXPECT_TRUE(redis.empty());
}

TEST(RedisLiteExistsStandalone, ExistsWithLargeDataset)
{
    RedisLite redis;

    for(int i = 0; i < 100; i++)
    {
        redis.set("key" + std::to_string(i),
                  "value" + std::to_string(i));
    }

    EXPECT_TRUE(redis.exists("key0"));
    EXPECT_TRUE(redis.exists("key50"));
    EXPECT_TRUE(redis.exists("key99"));

    EXPECT_FALSE(redis.exists("key100"));
}