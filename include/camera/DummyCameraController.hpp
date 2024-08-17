#pragma once

#include "CameraController.hpp"

namespace height_vision_pi
{
    class DummyCameraController : CameraController
    {
    public:
        explicit DummyCameraController(const CameraConfig& new_camera_config);
        void getFrame(cv::Mat& frame) override;
    };
}
