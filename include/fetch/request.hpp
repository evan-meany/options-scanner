#pragma once

#include "core/date.hpp"

#include <string>

namespace quant_scan::fetch
{
    struct OptionRequest
    {
        std::string symbol{};
        core::Date expiration_date{};
    };
}