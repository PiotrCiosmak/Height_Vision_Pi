#include <camera/ArduCamCameraController.hpp>

using namespace height_vision_pi;

int main()
{
    const auto camera_controller = std::make_unique<ArduCamCameraController>(CameraConfig{});
    cv::Mat frame;
    while (true)
    {
        camera_controller->getFrame(frame);
        if (cv::waitKey(1) == 'q') // Press 'q' to exit the loop
        {
            break;
        }
    }
}
