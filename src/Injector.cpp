#include "Injector.hpp"
#include "Logger.hpp"
#include "camera/ArduCamCameraController.hpp"
#include "camera/DummyCameraController.hpp"
#include "config/Config.hpp"
#include "monitor/Monitor.hpp"

#include <monitor/DummyMonitor.hpp>

using namespace height_vision_pi;

auto height_vision_pi::cameraControllerInjector()
    -> boost::di::injector<std::unique_ptr<CameraController>>
{
    switch (Config::get().data_source)
    {
    case DataSourceConfig::stream:
        return arduCamCameraControllerInjector();
    case DataSourceConfig::none:
        return dummyCameraControllerInjector();
    }
    Logger::error("Invalid data source. Check config file!");
    return dummyCameraControllerInjector();
}

auto height_vision_pi::dummyCameraControllerInjector()
    -> boost::di::injector<std::unique_ptr<CameraController>>
{
    return make_injector(
        boost::di::bind<CameraConfig>().to(Config::get().camera),
        boost::di::bind<CameraController>().to<DummyCameraController>().in(boost::di::unique));
}

auto height_vision_pi::arduCamCameraControllerInjector()
    -> boost::di::injector<std::unique_ptr<CameraController>>
{
    return make_injector(
        boost::di::bind<CameraConfig>().to(Config::get().camera),
        boost::di::bind<CameraController>().to<ArduCamCameraController>().in(boost::di::unique));
}
auto height_vision_pi::monitorDeviceInjector()
    -> boost::di::injector<std::unique_ptr<MonitorDevice>>
{
    switch (Config::get().data_source)
    {
    case DataSourceConfig::stream:
        return monitorInjector();
    case DataSourceConfig::none:
        return dummyMonitorInjector();
    }
    Logger::error("Invalid data source. Check config file!");
    return dummyMonitorInjector();
}

auto height_vision_pi::monitorInjector() -> boost::di::injector<std::unique_ptr<MonitorDevice>>
{
    return make_injector(boost::di::bind<MonitorConfig>().to(Config::get().monitor),
                         boost::di::bind<MonitorDevice>.to<DummyMonitor>().in(boost::di::unique));
}
auto height_vision_pi::dummyMonitorInjector() -> boost::di::injector<std::unique_ptr<MonitorDevice>>
{
    return make_injector(boost::di::bind<MonitorConfig>().to(Config::get().monitor),
                         boost::di::bind<MonitorDevice>.to<Monitor>().in(boost::di::unique));
}
