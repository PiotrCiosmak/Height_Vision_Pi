#include <camera/ArduCamCameraController.hpp>

using namespace height_vision_pi;

int main()
{
    const auto camera_controller = std::make_unique<ArduCamCameraController>(CameraConfig{});
    while (true)
    {
        auto captured_frame = camera_controller->getFrame();
        imshow("Dasd", captured_frame);
        if (cv::waitKey(1) == 'q')
        {
            break;
        }
    }
}
