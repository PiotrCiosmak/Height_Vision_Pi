#include "Injector.hpp"
#include "Logger.hpp"
#include "camera/ArduCamCameraController.hpp"
#include "config/Config.hpp"

#include <thread>

using namespace height_vision_pi;

int main()
{
    const std::chrono::milliseconds frame_duration{1000
                                                   / static_cast<int>(Config::get().camera.fps)};

    const auto monitor = monitorInjector().create<std::unique_ptr<MonitorDevice>>();
    const auto camera_controller =
        cameraControllerInjector().create<std::unique_ptr<CameraController>>();
    while (true)
    {
        const auto start_time = std::chrono::high_resolution_clock::now();
        monitor->checkCPUTemperature();
        auto frame = camera_controller->getFrame();
        if (!frame.empty())
        {
            imshow(Config::get().window.name, frame);
            cv::resizeWindow(Config::get().window.name,
                             Config::get().camera.resolution.x,
                             Config::get().camera.resolution.y);
        }
        if (cv::waitKey(1) == 'q')
        {
            break;
        }

        const auto end_time = std::chrono::high_resolution_clock::now();
        const auto elapsed_time = end_time - start_time;
        const auto sleep_duration =
            frame_duration - std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time);
        Logger::info("Main loop must wait: {} ms", sleep_duration);
        if (sleep_duration.count() > 0)
        {
            std::this_thread::sleep_for(sleep_duration);
        }
    }
}
