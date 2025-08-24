#include "financials/money.hpp"

#include <gtest/gtest.h>
#include <type_traits>
#include <cmath>

using namespace quant_scan::financials;

template <typename MoneyT>
class MoneyTypedTest : public ::testing::Test
{
};

using money_types = ::testing::Types<USD, EUR, GBP, JPY, KWD>;
TYPED_TEST_SUITE(MoneyTypedTest, money_types);

TYPED_TEST(MoneyTypedTest, from_double_and_as_double_round_trip)
{
    using money_t = TypeParam;

    // Pick a value with fractional part to test rounding for each minor_units
    const double value = 123.456789;

    const auto m = money_t::from_double(value);

    // Expected minor units = round(value * 10^minor_units)
    std::int64_t scale = 1;
    for (int i = 0; i < money_t::Traits::minor_units; ++i)
    {
        scale *= 10;
    }

    const auto expected_minor = static_cast<std::int64_t>(std::llround(value * static_cast<double>(scale)));
    EXPECT_EQ(m.minor, expected_minor);

    const double expected_double = static_cast<double>(expected_minor) / static_cast<double>(scale);
    EXPECT_NEAR(m.as_double(), expected_double, 1e-9);
}

TYPED_TEST(MoneyTypedTest, arithmetic_same_currency_only)
{
    using money_t = TypeParam;

    const auto a = money_t::from_double(1.10);
    const auto b = money_t::from_double(2.25);

    const auto c = a + b;
    EXPECT_EQ(c.minor, a.minor + b.minor);

    money_t d = a;
    d += b;
    EXPECT_EQ(d.minor, a.minor + b.minor);

    const auto e = b - a;
    EXPECT_EQ(e.minor, b.minor - a.minor);
}

TYPED_TEST(MoneyTypedTest, ordering_and_equality)
{
    using money_t = TypeParam;

    const auto a = money_t::from_double(5.00);
    const auto b = money_t::from_double(5.00);
    const auto c = money_t::from_double(6.00);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
    EXPECT_TRUE(a < c);
    EXPECT_TRUE(c > a);
}

// Non-typed checks for specific currency rules (minor_units differences)
TEST(MoneySpecificTest, jpy_has_zero_minor_units_rounding)
{
    const auto a = JPY::from_double(100.49);
    const auto b = JPY::from_double(100.50);

    // JPY rounds to whole yen
    EXPECT_EQ(a.minor, 100);
    EXPECT_EQ(b.minor, 101);
    EXPECT_DOUBLE_EQ(a.as_double(), 100.0);
    EXPECT_DOUBLE_EQ(b.as_double(), 101.0);
}

TEST(MoneySpecificTest, kwd_has_three_minor_units_rounding)
{
    const auto a = KWD::from_double(1.2344);
    const auto b = KWD::from_double(1.2345);

    // KWD rounds to 3 decimal places
    EXPECT_EQ(a.minor, 1234);  // 1.234
    EXPECT_EQ(b.minor, 1235);  // 1.235
    EXPECT_NEAR(a.as_double(), 1.234, 1e-12);
    EXPECT_NEAR(b.as_double(), 1.235, 1e-12);
}

// Compile-time sanity: currency types are distinct
static_assert(!std::is_same_v<USD, EUR>, "USD and EUR should be different Money types");
static_assert(std::is_same_v<USD, Money<Currency::USD>>, "USD alias must match Money<USD>");
