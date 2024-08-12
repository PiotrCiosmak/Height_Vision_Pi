#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main()
{
    cv::Mat frame;
    cv::VideoCapture cap(cv::CAP_LIBCAMERA);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 643); //Width selection, is auto adjusted for supported values
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 362); //Height Selection
    //cap.set(cv::CAP_PROP_MODE, 0); //PixelFormat Selection
    //cap.set(cv::CAP_PROP_FORMAT, 2); //StreamRole Selection
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
        return -1;
    }

    if (cap.read(frame))
    {
        // Assuming you may need to handle Bayer format
        // cv::cvtColor(frame, frame, cv::COLOR_BayerBG2BGR); // Uncomment if needed
        imshow("Original Video", frame);
        cv::waitKey(0); // To keep the window open
    }
    else
    {
        cout << "Failed to capture frame" << endl;
        return -1;
    }
    return 0;
}
