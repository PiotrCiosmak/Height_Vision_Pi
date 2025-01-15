#pragma once

#include "camera/CameraController.hpp"

#include <gmock/gmock.h>

namespace height_vision_pi
{
    class MockCameraController final : public CameraController
    {
    public:
        explicit MockCameraController() : CameraController{CameraConfig{}}
        {
        }

        MOCK_METHOD(cv::Mat, getFrame, (), (override));
    };
} // namespace height_vision_pi