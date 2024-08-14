#pragma once

#include "camera/CameraController.hpp"

namespace height_vision_pi
{
    class ArduCamCameraController final : public CameraController
    {
    public:
        explicit ArduCamCameraController(const CameraConfig& new_camera_config);
        auto getFrame() -> cv::Mat override;

    private:
        cv::VideoCapture video_capture;
    };
}
