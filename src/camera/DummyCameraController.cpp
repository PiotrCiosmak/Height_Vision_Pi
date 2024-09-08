#include "camera/DummyCameraController.hpp"
#include "Logger.hpp"

using namespace height_vision_pi;

//TODO path to config file
DummyCameraController::DummyCameraController() :
    CameraController{CameraConfig{}}, video_capture{std::make_unique<cv::VideoCapture>("../resources/camera_video.mp4")}
{
    if (!video_capture->isOpened())
    {
        Logger::error("Unable to open the video file");
    }
}

auto DummyCameraController::getFrame() -> cv::Mat
{
    auto frame = cv::Mat{};

    if (!video_capture->read(frame))
    {
        Logger::info("Looping video");
        video_capture->set(cv::CAP_PROP_POS_FRAMES, 0);
        video_capture->read(frame);
    }

    if (frame.empty())
    {
        Logger::warn("Captured frame from video file is empty");
    }

    return frame;
}
