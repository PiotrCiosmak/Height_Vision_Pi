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

void ArduCamCameraController::getFrame(cv::Mat& _)
{
    cv::Mat frame;
    cv::VideoCapture cap(cv::CAP_LIBCAMERA);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 2048); //Width selection, is auto adjusted for supported values
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 1537); //Height Selection
    cap.set(cv::CAP_PROP_MODE, true); //PixelFormat Selection
    cap.set(cv::CAP_PROP_FPS, 30); //PixelFormat Selection
    cap.set(cv::CAP_PROP_AUTOFOCUS, true); //PixelFormat Selection
    cap.set(cv::CAP_PROP_AUTO_EXPOSURE, true); //PixelFormat Selection
    if (!cap.isOpened() == true)
    {
        std::cout << "\nFalse" << std::endl;
    }

    while (true)
    {
        if (cap.read(frame))
        {
            imshow("Original Video", frame);

            if (cv::waitKey(1) == 'q') // Press 'q' to exit the loop
            {
                break;
            }
        }
    }
}
