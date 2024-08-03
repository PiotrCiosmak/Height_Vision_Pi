#pragma once

#include <libcamera/camera_manager.h>

class CameraController
{
public:
    CameraController();
    [[nodiscard]] auto getCamera(size_t index = 0) const -> std::shared_ptr<libcamera::Camera>;

private:
    std::unique_ptr<libcamera::CameraManager> camera_manager;
};
