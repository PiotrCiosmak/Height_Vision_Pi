#include "Injector.hpp"
#include "camera/DummyCameraController.hpp"
#include "monitor/DummyMonitor.hpp"
#ifdef AARCH64
#include "camera/ArduCamCameraController.hpp"
#include "monitor/Monitor.hpp"
#endif
#include "config/Config.hpp"

#include <gtest/gtest.h>

using namespace height_vision_pi;

TEST(InjectorTest, ShouldCreateCameraControllerInjector)
{
    auto injector = cameraControllerInjector();
    auto camera_controller = injector.create<std::unique_ptr<CameraController>>();
    EXPECT_NE(camera_controller, nullptr);
}

TEST(InjectorTest, ShouldCreateDummyCameraControllerInjector)
{
    auto injector = dummyCameraControllerInjector();
    auto camera_controller = injector.create<std::unique_ptr<CameraController>>();
    EXPECT_NE(camera_controller, nullptr);
    EXPECT_TRUE(dynamic_cast<DummyCameraController*>(camera_controller.get()) != nullptr);
}

#ifdef AARCH64
TEST(InjectorTest, ShouldCreateArduCamCameraControllerInjector)
{
    if (std::getenv("CI"))
    {
        GTEST_SKIP() << "Skipping MonitorInjector test on CI";
    }

    auto injector = arduCamCameraControllerInjector();
    auto camera_controller = injector.create<std::unique_ptr<CameraController>>();
    EXPECT_NE(camera_controller, nullptr);
    EXPECT_TRUE(dynamic_cast<ArduCamCameraController*>(camera_controller.get()) != nullptr);
}
#endif

TEST(InjectorTest, MonitorDeviceInjector)
{
    auto injector = monitorDeviceInjector();
    auto monitor_device = injector.create<std::unique_ptr<MonitorDevice>>();
    EXPECT_NE(monitor_device, nullptr);
}

TEST(InjectorTest, DummyMonitorInjector)
{
    auto injector = dummyMonitorInjector();
    auto monitor_device = injector.create<std::unique_ptr<MonitorDevice>>();
    EXPECT_NE(monitor_device, nullptr);
    EXPECT_TRUE(dynamic_cast<DummyMonitor*>(monitor_device.get()) != nullptr);
}

#ifdef AARCH64
TEST(InjectorTest, MonitorInjector)
{
    auto injector = monitorInjector();
    auto monitor_device = injector.create<std::unique_ptr<MonitorDevice>>();
    EXPECT_NE(monitor_device, nullptr);
    EXPECT_TRUE(dynamic_cast<Monitor*>(monitor_device.get()) != nullptr);
}
#endif

TEST(InjectorTest, HumanDetectorInjector)
{
    auto injector = humanDetectorInjector();
    auto human_detector = injector.create<std::unique_ptr<HumanDetector>>();
    EXPECT_NE(human_detector, nullptr);
}

TEST(InjectorTest, FaceDetectorInjector)
{
    auto injector = faceDetectorInjector();
    auto face_detector = injector.create<std::unique_ptr<FaceDetector>>();
    EXPECT_NE(face_detector, nullptr);
}

TEST(InjectorTest, AgeDetectorInjector)
{
    auto injector = ageDetectorInjector();
    auto age_detector = injector.create<std::unique_ptr<AgeDetector>>();
    EXPECT_NE(age_detector, nullptr);
}

TEST(InjectorTest, PupilsDistanceCalculatorInjector)
{
    auto injector = pupilsDistanceCalculatorInjector();
    auto pupils_distance_calculator = injector.create<std::unique_ptr<PupilsDistanceCalculator>>();
    EXPECT_NE(pupils_distance_calculator, nullptr);
}

TEST(InjectorTest, HeightCalculatorInjector)
{
    auto injector = heightCalculatorInjector();
    auto height_calculator = injector.create<std::unique_ptr<HeightCalculator>>();
    EXPECT_NE(height_calculator, nullptr);
}