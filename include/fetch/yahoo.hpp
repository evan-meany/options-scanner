#pragma once

#include <optional>

#include "fetch.hpp"

namespace quant_scan::fetch
{
    template <>
    struct Fetcher<Provider::yahoo>
    {
        template <typename Request>
        std::optional<typename Request::result_t> fetch(const Request& request)
        {
            // TODO
            return std::nullopt;
        }

    private:
        // dispatch requests?
    };
}