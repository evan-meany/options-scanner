#include "core/date.hpp"

#include <gtest/gtest.h>

using quant_scan::core::Date;

TEST(DateTest, FormatsIso8601)
{
    const Date date{2025, 8, 24};
    EXPECT_EQ(date.to_string(), "2025-08-24");
    EXPECT_TRUE(date.ymd.ok());
}

TEST(DateTest, InvalidDateIsNotOk)
{
    const Date date{2025, 2, 30};
    EXPECT_FALSE(date.ymd.ok());
    EXPECT_EQ(date.to_string(), "2025-02-30 is not a valid date");
}

TEST(DateTest, BoundaryValues)
{
    const Date date_1{1970, 1, 1};
    EXPECT_TRUE(date_1.ymd.ok());
    EXPECT_EQ(date_1.to_string(), "1970-01-01");

    const Date date_2{9999, 12, 31};
    EXPECT_TRUE(date_2.ymd.ok());
    EXPECT_EQ(date_2.to_string(), "9999-12-31");
}