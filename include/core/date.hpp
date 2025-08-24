#pragma once

#include <chrono>
#include <format>

namespace quant_scan::core
{
    struct Date
    {
        Date() = default;
        Date(const int year, const int month, const int day)
            : ymd(std::chrono::year(year), std::chrono::month(month), std::chrono::day(day))
        {}

        [[nodiscard]] std::string to_string() const { return std::format("{}", ymd); }

        std::chrono::year_month_day ymd{};
    };
}