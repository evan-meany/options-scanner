#include "financials/money.hpp"

#include <gtest/gtest.h>
#include <type_traits>
#include <cmath>

using namespace quant_scan::financials;

template <typename MoneyType>
class MoneyTypedTest : public ::testing::Test
{
};

using money_types = ::testing::Types<USD, EUR, GBP, JPY, KWD>;
TYPED_TEST_SUITE(MoneyTypedTest, money_types);

TYPED_TEST(MoneyTypedTest, from_double_and_as_double_round_trip)
{
    using money_t = TypeParam;

    constexpr double input_value = 123.456789;

    const auto money_value = money_t::from_double(input_value);

    std::int64_t scale_factor = 1;
    for (int index = 0; index < money_t::Traits::minor_units; ++index)
    {
        scale_factor *= 10;
    }

    const auto expected_minor_units = std::llround(input_value * static_cast<double>(scale_factor));
    EXPECT_EQ(expected_minor_units, money_value.minor);

    const double expected_double_value =
        static_cast<double>(expected_minor_units) / static_cast<double>(scale_factor);
    EXPECT_NEAR(expected_double_value, money_value.as_double(), 1e-9);
}

TYPED_TEST(MoneyTypedTest, arithmetic_same_currency_only)
{
    using money_t = TypeParam;

    const auto money_one = money_t::from_double(1.10);
    const auto money_two = money_t::from_double(2.25);

    const auto money_sum = money_one + money_two;
    EXPECT_EQ(money_one.minor + money_two.minor, money_sum.minor);

    money_t money_accumulated = money_one;
    money_accumulated += money_two;
    EXPECT_EQ(money_one.minor + money_two.minor, money_accumulated.minor);

    const auto money_difference = money_two - money_one;
    EXPECT_EQ(money_two.minor - money_one.minor, money_difference.minor);
}

TYPED_TEST(MoneyTypedTest, ordering_and_equality)
{
    using money_t = TypeParam;

    const auto money_low = money_t::from_double(5.00);
    const auto money_equal = money_t::from_double(5.00);
    const auto money_high = money_t::from_double(6.00);

    EXPECT_TRUE(money_low == money_equal);
    EXPECT_FALSE(money_low == money_high);
    EXPECT_TRUE(money_low < money_high);
    EXPECT_TRUE(money_high > money_low);
}

// Non-typed checks for specific currency rules (minor_units differences)
TEST(MoneySpecificTest, jpy_has_zero_minor_units_rounding)
{
    const auto yen_low = JPY::from_double(100.49);
    const auto yen_high = JPY::from_double(100.50);

    EXPECT_EQ(100, yen_low.minor);
    EXPECT_EQ(101, yen_high.minor);
    EXPECT_DOUBLE_EQ(100.0, yen_low.as_double());
    EXPECT_DOUBLE_EQ(101.0, yen_high.as_double());
}

TEST(MoneySpecificTest, kwd_has_three_minor_units_rounding)
{
    const auto dinar_low = KWD::from_double(1.2344);
    const auto dinar_high = KWD::from_double(1.2345);

    EXPECT_EQ(1234, dinar_low.minor);  // 1.234
    EXPECT_EQ(1235, dinar_high.minor); // 1.235
    EXPECT_NEAR(1.234, dinar_low.as_double(), 1e-12);
    EXPECT_NEAR(1.235, dinar_high.as_double(), 1e-12);
}

// Compile-time sanity: currency types are distinct
static_assert(!std::is_same_v<USD, EUR>, "USD and EUR should be different Money types");
static_assert(std::is_same_v<USD, Money<Currency::USD>>, "USD alias must match Money<USD>");
