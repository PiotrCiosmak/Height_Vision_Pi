#pragma once

#include "config/utils/CPUMonitor.hpp"

namespace height_vision_pi
{
    struct MonitorConfig
    {
        CPUMonitor cpu_monitor;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(MonitorConfig, cpu_monitor)
    };
} // namespace height_vision_pi