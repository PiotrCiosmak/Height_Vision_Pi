#pragma once

#include "monitor/MonitorDevice.hpp"

#include <gmock/gmock.h>

namespace height_vision_pi
{
    class MockMonitor : public MonitorDevice
    {
    public:
        explicit MockMonitor() : MonitorDevice{MonitorConfig{}} {}

        MOCK_METHOD(void, checkCPUTemperature, (), (override));
        MOCK_METHOD(void, checkCPUUsage, (), (override));
        MOCK_METHOD(void, checkDiskUsage, (), (override));
        MOCK_METHOD(void, checkRAMUsage, (), (override));
        MOCK_METHOD(void, checkGPUUsage, (), (override));
    };
} // namespace height_vision_pi
