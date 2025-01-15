#pragma once

#include "CameraController.hpp"

namespace height_vision_pi
{
    class DummyCameraController final : public CameraController
    {
    public:
        DummyCameraController();
        [[nodiscard]] auto getFrame() -> cv::Mat override;

    private:
        std::unique_ptr<cv::VideoCapture> video_capture;
    };
} // namespace height_vision_pi