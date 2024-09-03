#pragma once

#include "CameraController.hpp"

namespace height_vision_pi
{
    class DummyCameraController final : public CameraController
    {
    public:
        explicit DummyCameraController();
        [[nodiscard]] auto getFrame() -> cv::Mat override;
    };
} // namespace height_vision_pi
