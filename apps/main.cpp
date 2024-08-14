#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main()
{
    cv::Mat frame;
    cv::VideoCapture cap(cv::CAP_LIBCAMERA);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 2312); //Width selection, is auto adjusted for supported values
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 1736); //Height Selection
    cap.set(cv::CAP_PROP_FPS, 30);
    cap.set(cv::CAP_PROP_MODE, true); //PixelFormat Selection
    //cap.set(cv::CAP_PROP_FORMAT, 0); //StreamRole Selection
    auto brightness = cap.get(cv::CAP_PROP_BRIGHTNESS);
    std::cout << "brightness:" << brightness << std::endl;
    auto contrast = cap.get(cv::CAP_PROP_CONTRAST);
    std::cout << "contrast:" << contrast << std::endl;
    auto saturation = cap.get(cv::CAP_PROP_SATURATION);
    std::cout << "saturation:" << saturation << std::endl;
    auto hue = cap.get(cv::CAP_PROP_HUE);
    std::cout << "hue:" << hue << std::endl;
    auto gain = cap.get(cv::CAP_PROP_GAIN);
    std::cout << "gain:" << gain << std::endl;
    auto exposure = cap.get(cv::CAP_PROP_EXPOSURE);
    std::cout << "exposure:" << exposure << std::endl;


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

    while (true)
    {
        if (cap.read(frame))
        {
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
