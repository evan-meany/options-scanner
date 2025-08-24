#pragma once

#include <chrono>
#include <string>

namespace quant_scan::fetch
{


    struct OptionChain
    {
            using result_t = std::vector<>
        std::string symbol{};
        std::string expiration_date{};
    };
}