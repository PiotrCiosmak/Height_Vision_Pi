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

    std::string a = cap.getBackendName();
    cout << "Backend: " << a << std::endl;

    if (cap.isOpened() == true) {
        cout << "\nTrue" << std::endl;
    } else {
        cout << "False";
    }

    while (true) {
        if (cap.read(frame)) {
            imshow("Original Video", frame);
            int width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
            int height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

            if (cv::waitKey(1) == 'q') // Press 'q' to exit the loop
            {
                break;
            }
        }
    }
    return 0;
}