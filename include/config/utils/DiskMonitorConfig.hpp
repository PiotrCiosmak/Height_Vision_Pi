#pragma once

#include <nlohmann/json.hpp>

namespace height_vision_pi
{
    struct DiskMonitorConfig
    {
        std::string path;
        double warning_usage_percentage;
        double error_usage_percentage;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(DiskMonitorConfig,
                                       path,
                                       warning_usage_percentage,
                                       error_usage_percentage)
    };
} // namespace height_vision_pi
