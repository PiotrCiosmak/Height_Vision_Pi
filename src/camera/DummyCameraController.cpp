#include "camera/DummyCameraController.hpp"

using namespace height_vision_pi;

DummyCameraController::DummyCameraController(const CameraConfig& new_camera_config) :
    CameraController{new_camera_config}
{
}

auto DummyCameraController::getFrame() -> cv::Mat
{
    auto frame = cv::Mat{};
    return frame;
}
