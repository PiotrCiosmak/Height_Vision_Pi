#pragma once

#include <nlohmann/json.hpp>

namespace height_vision_pi
{
    struct CPUMonitorConfig
    {
        std::string thermal_zone_path;
        double warning_temperature;
        double error_temperature;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(CPUMonitorConfig,
                                       thermal_zone_path,
                                       warning_temperature,
                                       error_temperature)
    };
} // namespace height_vision_pi
