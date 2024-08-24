#pragma once

#include "camera/CameraController.hpp"

#include <boost/di.hpp>

namespace height_vision_pi
{
    template<typename T> using UniqueInjector = boost::di::injector<std::unique_ptr<T>>;
    [[nodiscard]] auto cameraControllerInjector() -> UniqueInjector<CameraController>;
    [[nodiscard]] auto dummyCameraControllerInjector() -> UniqueInjector<CameraController>;
    [[nodiscard]] auto arduCamCameraControllerInjector() -> UniqueInjector<CameraController>;
} // namespace height_vision_pi
