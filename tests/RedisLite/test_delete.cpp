#include <gtest/gtest.h>
#include "RedisLite.hpp"

class RedisLiteDeleteTest : public ::testing::Test
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

TEST_F(RedisLiteDeleteTest, DeleteExistingKey)
{
    EXPECT_TRUE(redis.del("city"));
    EXPECT_EQ(redis.size(), 2);

    std::string value;
    EXPECT_FALSE(redis.get("city", value));
}

TEST_F(RedisLiteDeleteTest, DeleteFirstKey)
{
    EXPECT_TRUE(redis.del("name"));

    EXPECT_EQ(redis.size(), 2);

    std::string value;
    EXPECT_FALSE(redis.get("name", value));
}

TEST_F(RedisLiteDeleteTest, DeleteLastKey)
{
    EXPECT_TRUE(redis.del("country"));

    EXPECT_EQ(redis.size(), 2);

    std::string value;
    EXPECT_FALSE(redis.get("country", value));
}

TEST_F(RedisLiteDeleteTest, DeleteNonExistingKey)
{
    EXPECT_FALSE(redis.del("age"));

    EXPECT_EQ(redis.size(), 3);
}

TEST_F(RedisLiteDeleteTest, DeleteKeyTwice)
{
    EXPECT_TRUE(redis.del("city"));
    EXPECT_FALSE(redis.del("city"));

    EXPECT_EQ(redis.size(), 2);
}

TEST_F(RedisLiteDeleteTest, DeleteAllKeys)
{
    EXPECT_TRUE(redis.del("name"));
    EXPECT_TRUE(redis.del("city"));
    EXPECT_TRUE(redis.del("country"));

    EXPECT_TRUE(redis.empty());
    EXPECT_EQ(redis.size(), 0);
}

TEST(RedisLiteDeleteStandalone, DeleteFromEmptyDatabase)
{
    RedisLite redis;

    EXPECT_FALSE(redis.del("key"));

    EXPECT_TRUE(redis.empty());
}

TEST(RedisLiteDeleteStandalone, DeleteOneAmongManyKeys)
{
    RedisLite redis;

    for(int i = 0; i < 100; i++)
    {
        redis.set("key" + std::to_string(i),
                  "value" + std::to_string(i));
    }

    EXPECT_TRUE(redis.del("key50"));

    EXPECT_EQ(redis.size(), 99);

    std::string value;

    EXPECT_FALSE(redis.get("key50", value));
    EXPECT_TRUE(redis.get("key49", value));
    EXPECT_TRUE(redis.get("key51", value));
}