#pragma once

#include "config/MonitorConfig.hpp"

namespace height_vision_pi
{
    class MonitorDevice
    {
    public:
        explicit MonitorDevice(const MonitorConfig& new_monitor_config) :
            monitor_config{new_monitor_config}
        {
        }

        virtual void checkCPUTemperature() = 0;
        virtual void checkCPUUsage() = 0;
        virtual void checkDiskUsage() = 0;
        virtual void checkRAMUsage() = 0;
        virtual void checkGPUUsage() = 0;

        virtual ~MonitorDevice() = default;

    protected:
        MonitorConfig monitor_config;
    };
} // namespace height_vision_pi