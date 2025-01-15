#pragma once

#include "monitor/MonitorDevice.hpp"

#include <gmock/gmock.h>

namespace height_vision_pi
{
    class MockMonitor : public MonitorDevice
    {
    public:
        explicit MockMonitor() : MonitorDevice{MonitorConfig{}} {}

        MOCK_METHOD(void, check, (), (override));
    };
} // namespace height_vision_pi