#pragma once

#include "monitor/MonitorDevice.hpp"

#include <gmock/gmock.h>

namespace height_vision_pi
{
    class MockMonitor : public MonitorDevice
    {
    public:
        explicit MockMonitor(const MonitorConfig& new_monitor_config) :
            MonitorDevice{new_monitor_config}
        {
        }

        MOCK_METHOD(void, checkCPUTemperature, (), (override));
    };
} // namespace height_vision_pi
