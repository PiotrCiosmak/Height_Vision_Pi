#pragma once

#include "camera/CameraController.hpp"
#include "detector/FaceDetector.hpp"
#include "detector/HumanDetector.hpp"
#include "monitor/MonitorDevice.hpp"
#include "detector/AgeDetector.hpp"
#include "calculator/PupilsDistanceCalculator.hpp"

#include <boost/di.hpp>

namespace height_vision_pi
{
    template <typename T>
    using UniqueInjector = boost::di::injector<std::unique_ptr<T>>;

    [[nodiscard]] auto cameraControllerInjector() -> UniqueInjector<CameraController>;
    [[nodiscard]] auto dummyCameraControllerInjector() -> UniqueInjector<CameraController>;
#ifdef AARCH64
    [[nodiscard]] auto arduCamCameraControllerInjector() -> UniqueInjector<CameraController>;
#endif
    [[nodiscard]] auto monitorDeviceInjector() -> UniqueInjector<MonitorDevice>;
    [[nodiscard]] auto dummyMonitorInjector() -> UniqueInjector<MonitorDevice>;
#ifdef AARCH64
    [[nodiscard]] auto monitorInjector() -> UniqueInjector<MonitorDevice>;
#endif
    [[nodiscard]] auto humanDetectorInjector() -> UniqueInjector<HumanDetector>;
    [[nodiscard]] auto faceDetectorInjector() -> UniqueInjector<FaceDetector>;
    [[nodiscard]] auto ageDetectorInjector() -> UniqueInjector<AgeDetector>;
    [[nodiscard]] auto pupilsDistanceCalculatorInjector() -> UniqueInjector<PupilsDistanceCalculator>;
} // namespace height_vision_pi