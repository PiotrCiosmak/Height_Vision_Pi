#include "Injector.hpp"

#include "camera/DummyCameraController.hpp"
#include "config/Config.hpp"
#include "camera/ArduCamCameraController.hpp"

using namespace height_vision_pi;


auto height_vision_pi::cameraControllerInjector() -> boost::di::injector<std::unique_ptr<CameraController>>
{
    switch (Config::get().data_source)
    {
    case DataSourceConfig::stream:
        return arduCamCameraControllerInjector();
    case DataSourceConfig::none:
        return dummyCameraControllerInjector();
    }
    std::cerr << "ERROR: Invalid data source. Check config file!" << std::endl;
    exit(1);
}


auto height_vision_pi::dummyCameraControllerInjector() -> boost::di::injector<std::unique_ptr<CameraController>>
{
    return make_injector(
        boost::di::bind<CameraConfig>().to(Config::get().camera),
        boost::di::bind<CameraController>().to<DummyCameraController>().in(boost::di::unique));
}

auto height_vision_pi::arduCamCameraControllerInjector() -> boost::di::injector<std::unique_ptr<CameraController>>
{
    return make_injector(
        boost::di::bind<CameraConfig>().to(Config::get().camera),
        boost::di::bind<CameraController>().to<ArduCamCameraController>().in(boost::di::unique));
}