#include "camera/CameraCapture.hpp"

using namespace height_vision_pi;

int main()
{
    CameraCapture cameraCapture{};
    cameraCapture.startCapture();
    return 0;
}
