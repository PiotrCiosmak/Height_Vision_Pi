#include "camera/ArduCamCameraController.hpp"

using namespace height_vision_pi;

ArduCamCameraController::ArduCamCameraController(const CameraConfig& new_camera_config) :
    CameraController(new_camera_config),
    video_capture(cv::CAP_LIBCAMERA)
{
    video_capture.set(cv::CAP_PROP_FRAME_WIDTH, camera_config.resolution.x);
    video_capture.set(cv::CAP_PROP_FRAME_HEIGHT, camera_config.resolution.y);
    video_capture.set(cv::CAP_PROP_FPS, camera_config.fps);
    video_capture.set(cv::CAP_PROP_MODE, camera_config.capture_mode);
    //video_capture.set(cv::CAP_PROP_BRIGHTNESS, camera_config.brightness);
    //video_capture.set(cv::CAP_PROP_SATURATION, camera_config.saturation);
    //video_capture.set(cv::CAP_PROP_HUE, camera_config.hue);
    //video_capture.set(cv::CAP_PROP_GAIN, camera_config.gain);
    video_capture.set(cv::CAP_PROP_AUTOFOCUS, camera_config.auto_focus);
    video_capture.set(cv::CAP_PROP_AUTO_EXPOSURE, camera_config.auto_exposure);
    if (!video_capture.isOpened())
    {
        std::cerr << "ERROR: Camera isn't working" << std::endl;
    }
}

auto ArduCamCameraController::getFrame() -> cv::Mat
{
    cv::Mat frame;
    if (!video_capture.read(frame))
    {
        std::cerr << "ERROR: Can't capture frame" << std::endl;
    }
    if (frame.empty())
    {
        std::cerr << "ERROR: Captured frame is empty" << std::endl;
    }
    cv::imshow("Das", frame);
    return frame.clone();
}
