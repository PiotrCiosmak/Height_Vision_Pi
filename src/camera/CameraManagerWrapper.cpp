#include "camera/CameraManagerWrapper.hpp"

using namespace height_vision_pi;

CameraManagerWrapper::CameraManagerWrapper() : camera_manager{std::make_unique<libcamera::CameraManager>()}
{
    if (camera_manager->start())
    {
        std::cerr << "ERROR: Failed to start camera manager" << std::endl;
        exit(1);
    }
}

auto CameraManagerWrapper::getCameras() const -> std::vector<std::shared_ptr<libcamera::Camera>>
{
    auto cameras = camera_manager->cameras();
    if (cameras.empty())
    {
        std::cerr << "ERROR: No cameras found" << std::endl;
        exit(1);
    }
    return cameras;
}

CameraManagerWrapper::~CameraManagerWrapper()
{
    camera_manager->stop();
}
