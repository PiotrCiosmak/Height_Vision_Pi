#include "camera/ArduCamCameraController.hpp"
#include "config/WindowConfig.hpp"

#include <thread>

using namespace height_vision_pi;

int main()
{
    const auto camera_config = CameraConfig{};
    const std::chrono::milliseconds frame_duration{1000 / camera_config.fps};

    const auto camera_controller = std::make_unique<ArduCamCameraController>(CameraConfig{});
    const auto window_config = WindowConfig{};
    while (true)
    {
        const auto start_time = std::chrono::high_resolution_clock::now();
        auto frame = camera_controller->getFrame();
        if (!frame.empty())
        {
            imshow(window_config.name, frame);
            cv::resizeWindow(window_config.name, window_config.resolution.x, window_config.resolution.y);
        }
        if (cv::waitKey(1) == 'q')
        {
            break;
        }

        const auto end_time = std::chrono::high_resolution_clock::now();
        const auto elapsed_time = end_time - start_time;
        auto sleep_duration = frame_duration - std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time);
        std::cout << "sleep_duration: " << sleep_duration << std::endl;
        if (sleep_duration.count() > 0)
        {
            std::this_thread::sleep_for(sleep_duration);
        }
    }
}
