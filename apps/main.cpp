#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main()
{
    cv::VideoCapture cap(cv::CAP_LIBCAMERA);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 4096); //Width selection, is auto adjusted for supported values
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 3074); //Height Selection
    cap.set(cv::CAP_PROP_MODE, 1); //PixelFormat Selection
    cap.set(cv::CAP_PROP_FORMAT, 2); //StreamRole Selection
    cap.set(cv::CAP_PROP_FORMAT, CV_8UC1);

    std::string a = cap.getBackendName();
    cout << "Backend: " << a << std::endl;

    if (cap.isOpened() == true)
    {
        cout << "\nTrue" << std::endl;
    }
    else
    {
        cout << "False";
    }

    cv::Mat frame;

    for (int i = 0; i < 20; ++i)
    {
        if (cap.read(frame))
        {
            imwrite("captured_frame.jpg", frame);
            std::cout << "Klatka została zapisana jako captured_frame.jpg" << std::endl;
        }
    }
    return 0;
}
