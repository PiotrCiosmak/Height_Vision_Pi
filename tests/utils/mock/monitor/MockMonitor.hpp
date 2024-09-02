#pragma once

#include "monitor/DeviceMonitor.hpp"

#include <gmock/gmock.h>

namespace height_vision_pi
{
    class MockMonitor : public DeviceMonitor
    {
    public:
        explicit MockMonitor(const MonitorConfig& new_monitor_config) :
            DeviceMonitor{new_monitor_config}
        {
        }

        MOCK_METHOD(void, checkCPUTemperature, (), (override));
    };
} // namespace height_vision_pi
