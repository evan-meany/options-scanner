#pragma once

#include <chrono>
#include <format>

namespace quant_scan::core
{
    struct Date
    {
        std::chrono::year_month_day ymd{};

        [[nodiscard]] std::string to_string() const { return std::format("{}", ymd); }
    };
}