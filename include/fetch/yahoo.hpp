#pragma once

#include <iostream>
#include <optional>

#include "fetch.hpp"
#include "request.hpp"

namespace quant_scan::fetch
{
    template <>
    struct Fetcher<Provider::yahoo>
    {
        template <typename Request>
        std::optional<typename Request::result_t> fetch(const Request& request)
        {
            if constexpr (std::is_same_v<Request, OptionRequest>)
            {
                std::cout << request.symbol << std::endl;
            }
            return std::nullopt;
        }

    private:
        // dispatch requests?
    };
}