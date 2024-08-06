#pragma once

#include "CameraManagerWrapper.hpp"

namespace height_vision_pi
{
    class CameraCapture
    {
    public:
        CameraCapture();
        void startCapture();

    private:
        CameraManagerWrapper camera_manager_wrapper;
    };
}
