#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main()
{
    cv::Mat frame;
    cv::VideoCapture cap(cv::CAP_LIBCAMERA);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 643); //Width selection, is auto adjusted for supported values
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 362); //Height Selection
    cap.set(cv::CAP_PROP_MODE, 1); //PixelFormat Selection
    cap.set(cv::CAP_PROP_FORMAT, 2); //StreamRole Selection
    cap.set(cv::CAP_PROP_FORMAT, CV_8UC1);

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

            if (cv::waitKey(1) == 'q') // Press 'q' to exit the loop
            {
                break;
            }
        }
    }
    return 0;
}