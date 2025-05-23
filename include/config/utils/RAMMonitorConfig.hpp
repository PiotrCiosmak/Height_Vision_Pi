#pragma once

#include <nlohmann/json.hpp>

namespace height_vision_pi
{
    struct RAMMonitorConfig
    {
        double warning_usage;
        double error_usage;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(RAMMonitorConfig,
                                       warning_usage,
                                       error_usage)
    };
} // namespace height_vision_pi