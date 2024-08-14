#include <camera/ArduCamCameraController.hpp>

using namespace height_vision_pi;

int main()
{
    const auto camera_controller = std::make_unique<ArduCamCameraController>(CameraConfig{});

    while (true)
    {
        cv::Mat frame;
        camera_controller->getFrame(frame);
        imshow("NAZWA_OKNA", frame);
    }
}
