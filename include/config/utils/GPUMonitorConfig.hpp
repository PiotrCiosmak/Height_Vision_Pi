#pragma once

#include <nlohmann/json.hpp>

namespace height_vision_pi
{
    struct GPUMonitorConfig
    {
        int warning_usage;
        int error_usage;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(GPUMonitorConfig,
                                       warning_usage,
                                       error_usage)
    };
} // namespace height_vision_pi
