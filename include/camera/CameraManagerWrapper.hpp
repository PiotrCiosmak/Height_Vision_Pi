#pragma once

#include <memory>
#include <vector>

#include <libcamera/camera.h>
#include <libcamera/camera_manager.h>

namespace height_vision_pi
{
    class CameraManagerWrapper
    {
    public:
        CameraManagerWrapper();
        [[nodiscard]] auto getCameras() const -> std::vector<std::shared_ptr<libcamera::Camera>>;;
        ~CameraManagerWrapper();

    private:
        std::unique_ptr<libcamera::CameraManager> camera_manager;
    };
}
