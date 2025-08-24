#pragma once

namespace quant_scan::fetch
{
    enum class Provider
    {
        yahoo = 0, polygon, databento
    };

    template <Provider provider>
    struct Fetcher;
}