#include "camera/CameraController.hpp"

#include <iostream>

using namespace libcamera;

CameraController::CameraController() : camera_manager{std::make_unique<CameraManager>()}
{
    if (camera_manager->start())
    {
        std::cerr << "ERROR: Failed to start camera manager" << std::endl;
        exit(1);
    }
}

auto CameraController::getCamera(const size_t index) const -> std::shared_ptr<Camera>
{
    auto cameras = camera_manager->cameras();
    if (cameras.empty())
    {
        std::cerr << "ERROR: No cameras found" << std::endl;
        exit(1);
    }
    return cameras.at(index);
}
