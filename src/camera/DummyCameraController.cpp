#include "camera/DummyCameraController.hpp"

using namespace height_vision_pi;

DummyCameraController::DummyCameraController(const CameraConfig& new_camera_config) : CameraController{
    new_camera_config
}
{
}

auto DummyCameraController::getFrame() -> cv::Mat&
{
    return cv::Mat{};
}

/*
auto getFrame() -> cv::Mat&
{
    //const auto camera_resolution = camera_config.resolution;
    //auto frame = cv::Mat::ones(camera_resolution.x, camera_resolution.y, CV_8UC3) * 255;
}
*/
