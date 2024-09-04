#pragma once

#include "config/utils/CPUMonitorConfig.hpp"
#include "config/utils/DiskMonitorConfig.hpp"

namespace height_vision_pi
{
    struct MonitorConfig
    {
        CPUMonitorConfig cpu_monitor;
        DiskMonitorConfig disk_monitor;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(MonitorConfig, cpu_monitor, disk_monitor)
    };
} // namespace height_vision_pi