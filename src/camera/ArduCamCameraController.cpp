#include "camera/ArduCamCameraController.hpp"
#include "Logger.hpp"

#include <opencv2/opencv.hpp>

using namespace height_vision_pi;

ArduCamCameraController::ArduCamCameraController(const CameraConfig& new_camera_config) :
    CameraController{new_camera_config},
    video_capture{std::make_unique<cv::VideoCapture>(cv::CAP_LIBCAMERA)}
{
    if (!video_capture->isOpened())
    {
        Logger::error("Camera isn't working");
    }
    video_capture->set(cv::CAP_PROP_BUFFERSIZE, 2);
    video_capture->set(cv::CAP_PROP_FRAME_WIDTH, camera_config.resolution.x);
    video_capture->set(cv::CAP_PROP_FRAME_HEIGHT, camera_config.resolution.y);
    video_capture->set(cv::CAP_PROP_FPS, camera_config.fps);
    video_capture->set(cv::CAP_PROP_MODE, camera_config.capture_mode);
    video_capture->set(cv::CAP_PROP_BRIGHTNESS, camera_config.brightness);
    video_capture->set(cv::CAP_PROP_SATURATION, camera_config.saturation);
    video_capture->set(cv::CAP_PROP_HUE, camera_config.hue);
    video_capture->set(cv::CAP_PROP_GAIN, camera_config.gain);
    video_capture->set(cv::CAP_PROP_AUTOFOCUS, camera_config.auto_focus);
    video_capture->set(cv::CAP_PROP_AUTO_EXPOSURE, camera_config.auto_exposure);
}

auto ArduCamCameraController::getFrame() -> cv::Mat
{
    cv::Mat tmp_frame;
    if (!video_capture->read(tmp_frame))
    {
        Logger::warn("Can't capture frame");
    }

    auto frame = tmp_frame.clone();
    if (frame.empty())
    {
        Logger::warn("Captured frame is empty");
    }
    return frame;
}

ArduCamCameraController::~ArduCamCameraController()
{
    if (!system("fuser -k /dev/media2"))
    {
        Logger::warn("Can't remove /dev/media2");
    }
    if (video_capture && video_capture->isOpened())
    {
        video_capture->release();
    }
}