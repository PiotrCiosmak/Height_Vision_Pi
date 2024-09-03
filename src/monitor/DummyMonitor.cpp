#include "monitor/DummyMonitor.hpp"
#include "Logger.hpp"

using namespace height_vision_pi;

DummyMonitor::DummyMonitor(const MonitorConfig& new_monitor_config) :
    MonitorDevice{new_monitor_config}
{
}

void DummyMonitor::checkCPUTemperature()
{
    Logger::info("Dummy Monitor doesn't know CPU temperature.");
}