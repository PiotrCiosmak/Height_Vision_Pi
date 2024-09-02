#pragma once

#include "monitor/DeviceMonitor.hpp"

#include <gmock/gmock.h>

namespace height_vision_pi
{
    class MockMonitor final : public DeviceMonitor
    {
    public:
        MOCK_METHOD(void, checkCPUTemperature, (), (override));
    };
} // namespace height_vision_pi
