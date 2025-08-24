#pragma once

#include "core/date.hpp"
#include <string>

namespace quant_scan::financials
{
    struct Option
    {
        enum class Type { call = 0, put };

        Type type{};
        size_t quantity{};
        double strike_price{};
        quant_scan::core::Date expiration_date{};
    };
}