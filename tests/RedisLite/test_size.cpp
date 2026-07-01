#include <gtest/gtest.h>
#include "RedisLite.hpp"

class RedisLiteSizeTest : public ::testing::Test
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

TEST_F(RedisLiteSizeTest, InitialSize)
{
    EXPECT_EQ(redis.size(), 3);
}

TEST_F(RedisLiteSizeTest, SizeAfterInsertion)
{
    redis.set("language", "C++");

    EXPECT_EQ(redis.size(), 4);
}

TEST_F(RedisLiteSizeTest, SizeAfterUpdatingExistingKey)
{
    redis.set("name", "Aman");

    EXPECT_EQ(redis.size(), 3);
}

TEST_F(RedisLiteSizeTest, SizeAfterDeletion)
{
    redis.del("city");

    EXPECT_EQ(redis.size(), 2);
}

TEST_F(RedisLiteSizeTest, SizeAfterClear)
{
    redis.clear();

    EXPECT_EQ(redis.size(), 0);
    EXPECT_TRUE(redis.empty());
}

TEST(RedisLiteSizeStandalone, EmptyDatabaseSize)
{
    RedisLite redis;

    EXPECT_EQ(redis.size(), 0);
}

TEST(RedisLiteSizeStandalone, LargeDatabaseSize)
{
    RedisLite redis;

    for(int i = 0; i < 1000; i++)
    {
        redis.set("key" + std::to_string(i),
                  "value" + std::to_string(i));
    }

    EXPECT_EQ(redis.size(), 1000);
}

TEST(RedisLiteSizeStandalone, SizeAfterMixedOperations)
{
    RedisLite redis;

    redis.set("A", "1");
    redis.set("B", "2");
    redis.set("C", "3");

    EXPECT_EQ(redis.size(), 3);

    redis.del("B");

    EXPECT_EQ(redis.size(), 2);

    redis.set("D", "4");

    EXPECT_EQ(redis.size(), 3);

    redis.clear();

    EXPECT_EQ(redis.size(), 0);
}