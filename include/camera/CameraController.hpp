#pragma once
#include "config/CameraConfig.hpp"

#include <opencv2/opencv.hpp>

namespace height_vision_pi
{
    class CameraController
    {
    public:
        explicit CameraController(const CameraConfig& new_camera_config): camera_config{new_camera_config}
        {
        }

        virtual void getFrame(cv::Mat& frame) =0;
        virtual ~CameraController() = default;

    protected:
        CameraConfig camera_config;
    };
}
