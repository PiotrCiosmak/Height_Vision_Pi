#include <thread>

#include "camera/ArduCamCameraController.hpp"
//#include "config/WindowConfig.hpp"

using namespace height_vision_pi;

int main()
{
    const auto camera_controller = std::make_unique<ArduCamCameraController>(CameraConfig{});
    //const auto window_config = WindowConfig{};
    while (true)
    {
        auto frame = camera_controller->getFrame();
        imshow("Height_Vision_Pi"/*window_config.name*/, frame);
        //cv::resizeWindow(window_config.name, window_config.resolution.x, window_config.resolution.y);
        if (cv::waitKey(1) == 'q')
        {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
