#pragma once

#include <nlohmann/json.hpp>
#include <filesystem>

namespace height_vision_pi
{
    struct CPUMonitorConfig
    {
        std::filesystem::path thermal_zone_path;
        double warning_temperature;
        double error_temperature;
        std::filesystem::path usage_path;
        int warning_usage;
        int error_usage;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(CPUMonitorConfig,
                                       thermal_zone_path,
                                       warning_temperature,
                                       error_temperature,
                                       usage_path,
                                       warning_usage,
                                       error_usage)
    };
} // namespace height_vision_pi
