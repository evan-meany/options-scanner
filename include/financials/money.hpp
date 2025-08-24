#pragma once
#include <cmath>
#include <cstdint>

namespace quant_scan::financials
{

    enum class Currency { USD, EUR, GBP, JPY, KWD };

    namespace details
    {
        template<Currency> struct CurrencyTraits;

        template<> struct CurrencyTraits<Currency::USD>
        {
            static constexpr int minor_units = 2;
            static constexpr const char* symbol = "$";
        };

        template<> struct CurrencyTraits<Currency::EUR>
        {
            static constexpr int minor_units = 2;
            static constexpr const char* symbol = "€";
        };

        template<> struct CurrencyTraits<Currency::GBP>
        {
            static constexpr int minor_units = 2;
            static constexpr const char* symbol = "£";
        };

        template<> struct CurrencyTraits<Currency::JPY>
        {
            static constexpr int minor_units = 0;
            static constexpr const char* symbol = "¥";
        };

        template<> struct CurrencyTraits<Currency::KWD>
        {
            static constexpr int minor_units = 3;
            static constexpr const char* symbol = "KD ";
        };
    }

    template<Currency currency>
    struct Money
    {
        using Traits = details::CurrencyTraits<currency>;
        std::int64_t minor{}; // e.g. cents, fils, sen

        constexpr Money() = default;
        explicit constexpr Money(std::int64_t money) : minor(money) {}

        static constexpr Money from_double(const double money)
        {
            // scale by 10^minor_units with rounding
            std::int64_t scale = 1;
            for (int i = 0; i < Traits::minor_units; ++i) scale *= 10;
            return Money{ static_cast<std::int64_t>(std::llround(money * scale)) };
        }

        [[nodiscard]] constexpr double as_double() const
        {
            std::int64_t scale = 1;
            for (int i = 0; i < Traits::minor_units; ++i) scale *= 10;
            return static_cast<double>(minor) / static_cast<double>(scale);
        }

        friend constexpr Money operator+(Money a, Money b) { a.minor += b.minor; return a; }
        friend constexpr Money operator-(Money a, Money b) { a.minor -= b.minor; return a; }
        constexpr Money& operator+=(Money b){ minor += b.minor; return *this; }
        constexpr Money& operator-=(Money b){ minor -= b.minor; return *this; }

        friend constexpr bool operator==(Money a, Money b){ return a.minor == b.minor; }
        friend constexpr auto operator<=>(const Money&, const Money&) = default;
    };

    using USD = Money<Currency::USD>;
    using EUR = Money<Currency::EUR>;
    using GBP = Money<Currency::GBP>;
    using JPY = Money<Currency::JPY>;
    using KWD = Money<Currency::KWD>;
}
