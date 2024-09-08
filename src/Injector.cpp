#include "Injector.hpp"
#include "Logger.hpp"
#include "camera/ArduCamCameraController.hpp"
#include "camera/DummyCameraController.hpp"
#include "config/Config.hpp"
#include "monitor/DummyMonitor.hpp"
#include "monitor/Monitor.hpp"

using namespace height_vision_pi;

auto height_vision_pi::cameraControllerInjector()
    -> boost::di::injector<std::unique_ptr<CameraController>>
{
    switch (Config::get().data_source)
    {
#ifdef ARCH_ARM
    case DataSourceConfig::stream:
        return arduCamCameraControllerInjector();
#endif
    case DataSourceConfig::file:
        return dummyCameraControllerInjector();
    }
    Logger::error("Invalid data source. Check config file!");
    return dummyCameraControllerInjector();
}

auto height_vision_pi::dummyCameraControllerInjector()
    -> boost::di::injector<std::unique_ptr<CameraController>>
{
    return make_injector(
        boost::di::bind<CameraController>().to<DummyCameraController>().in(boost::di::unique));
}

#ifdef ARCH_ARM
auto height_vision_pi::arduCamCameraControllerInjector()
    -> boost::di::injector<std::unique_ptr<CameraController>>
{
    return make_injector(
        boost::di::bind<CameraConfig>().to(Config::get().camera),
        boost::di::bind<CameraController>().to<ArduCamCameraController>().in(boost::di::unique));
}
#endif

auto height_vision_pi::monitorDeviceInjector()
    -> boost::di::injector<std::unique_ptr<MonitorDevice>>
{
    switch (Config::get().data_source)
    {
    case DataSourceConfig::stream:
        return monitorInjector();
    case DataSourceConfig::file:
        return dummyMonitorInjector();
    }
    Logger::error("Invalid data source. Check config file!");
    return dummyMonitorInjector();
}

auto height_vision_pi::dummyMonitorInjector() -> boost::di::injector<std::unique_ptr<MonitorDevice>>
{
    return make_injector(boost::di::bind<MonitorDevice>.to<DummyMonitor>().in(boost::di::unique));
}

auto height_vision_pi::monitorInjector() -> boost::di::injector<std::unique_ptr<MonitorDevice>>
{
    return make_injector(boost::di::bind<MonitorConfig>().to(Config::get().monitor),
                         boost::di::bind<MonitorDevice>.to<Monitor>().in(boost::di::unique));
}

auto height_vision_pi::humanDetectorInjector() -> UniqueInjector<HumanDetector>
{
    return make_injector(boost::di::bind<HumanDetector>.to<HumanDetector>().in(boost::di::unique));
}
