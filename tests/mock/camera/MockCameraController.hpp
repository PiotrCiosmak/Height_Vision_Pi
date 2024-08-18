#pragma once

#include "camera/CameraController.hpp"

#include <gmock/gmock.h>

namespace height_vision_pi
{
    class MockCameraController final : public CameraController
    {
    public:
        explicit MockCameraController(const CameraConfig& new_camera_config): CameraController{new_camera_config}
        {
        }

        MOCK_METHOD(cv::Mat, getFrame, (), (override));
    };
}
