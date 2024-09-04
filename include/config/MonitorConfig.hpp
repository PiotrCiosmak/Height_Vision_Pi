#pragma once

#include "config/utils/CPUMonitor.hpp"
#include "config/utils/DiskMonitorConfig.hpp"

namespace height_vision_pi
{
    struct MonitorConfig
    {
        CPUMonitor cpu_monitor;
        DiskMonitorConfig disk_monitor;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(MonitorConfig, cpu_monitor, disk_monitor)
    };
} // namespace height_vision_pi