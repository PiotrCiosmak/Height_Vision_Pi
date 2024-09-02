#pragma once

#include "config/MonitorConfig.hpp"

namespace height_vision_pi
{
    class DeviceMonitor
    {
    public:
        explicit DeviceMonitor(const MonitorConfig& new_monitor_config) :
            monitor_config{new_monitor_config}
        {
        }

        virtual void checkCPUTemperature() = 0;
        virtual ~DeviceMonitor() = default;

    protected:
        MonitorConfig monitor_config;
    };
} // namespace height_vision_pi