#pragma once

#include "monitor/MonitorDevice.hpp"

namespace height_vision_pi
{
    class DummyMonitor final : public MonitorDevice
    {
    public:
        DummyMonitor();
        void check() override{};
    };
} // namespace height_vision_pi