#pragma once

#include "camera/CameraController.hpp"
#include "detector/HumanDetector.hpp"
#include "monitor/MonitorDevice.hpp"

#include <boost/di.hpp>

namespace height_vision_pi
{
    template<typename T> using UniqueInjector = boost::di::injector<std::unique_ptr<T>>;
    [[nodiscard]] auto cameraControllerInjector() -> UniqueInjector<CameraController>;
    [[nodiscard]] auto dummyCameraControllerInjector() -> UniqueInjector<CameraController>;
#ifdef ARCH_ARM
    [[nodiscard]] auto arduCamCameraControllerInjector() -> UniqueInjector<CameraController>;
#endif
    [[nodiscard]] auto monitorDeviceInjector() -> UniqueInjector<MonitorDevice>;
    [[nodiscard]] auto dummyMonitorInjector() -> UniqueInjector<MonitorDevice>;
    [[nodiscard]] auto monitorInjector() -> UniqueInjector<MonitorDevice>;
    [[nodiscard]] auto humanDetectorInjector() -> UniqueInjector<HumanDetector>;
} // namespace height_vision_pi
