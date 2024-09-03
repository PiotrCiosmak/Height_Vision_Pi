#include "camera/DummyCameraController.hpp"

using namespace height_vision_pi;

DummyCameraController::DummyCameraController() : CameraController{CameraConfig{}} {}

auto DummyCameraController::getFrame() -> cv::Mat
{
    auto frame = cv::Mat{};
    return frame;
}
