#include <camera/ArduCamCameraController.hpp>

using namespace height_vision_pi;

int main()
{
    const auto camera_controller = std::make_unique<ArduCamCameraController>(CameraConfig{});

    while (true)
    {
        auto frame = camera_controller->getFrame();
        imshow("NAZWA", frame);
    }
}
