#include <camera/ArduCamCameraController.hpp>

using namespace height_vision_pi;

int main()
{
    const auto camera_controller = std::make_unique<ArduCamCameraController>(CameraConfig{});
    cv::Mat frame;
    camera_controller->getFrame(frame);

/*cv::Mat frame;
while (true)
{
    camera_controller->getFrame(frame);
    //imshow("dasda", frame);TODO FIX
    if (cv::waitKey(1) == 'q') // Press 'q' to exit the loop
    {
        break;
    }
}
}*/

//TODO 1. Make DummyCameraController
//TODO 2. Test for CameraController

/*
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main()
{
    cv::Mat frame;
    cv::VideoCapture cap(cv::CAP_LIBCAMERA);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 2048); //Width selection, is auto adjusted for supported values
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 1537); //Height Selection
    cap.set(cv::CAP_PROP_MODE, true); //PixelFormat Selection
    cap.set(cv::CAP_PROP_FPS, 30); //PixelFormat Selection
    cap.set(cv::CAP_PROP_AUTOFOCUS, true); //PixelFormat Selection
    cap.set(cv::CAP_PROP_AUTO_EXPOSURE, true); //PixelFormat Selection
    if (!cap.isOpened() == true)
    {
        cout << "\nFalse" << std::endl;
    }

    while (true)
    {
        if (cap.read(frame))
        {
            imshow("Original Video", frame);

            if (cv::waitKey(1) == 'q') // Press 'q' to exit the loop
            {
                break;
            }
        }
    }
    return 0;
}
*/
