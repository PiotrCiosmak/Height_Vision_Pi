#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main()
{
    cv::Mat frame;
    cv::VideoCapture cap(cv::CAP_LIBCAMERA);

    // Ustaw rozdzielczość na rozmiar wspierany przez kamerę
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 4624); // Szerokość, dostosowana do kamery
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 3472); // Wysokość, dostosowana do kamery

    std::string backendName = cap.getBackendName();
    cout << "Backend: " << backendName << std::endl;

    if (!cap.isOpened())
    {
        cout << "Failed to open the camera." << endl;
        return -1;
    }
    else
    {
        cout << "Camera successfully opened." << std::endl;
    }

    if (cap.read(frame))
    {
        std::cout<<"TYPE!!"<<frame.type()<<std::endl;
        // Konwertuj obraz z formatu Bayera na BGR
        cv::Mat bgrImage;
        cv::cvtColor(frame, bgrImage, cv::COLOR_BayerRG2BGR); // Zmien na odpowiedni format Bayera

        imshow("Captured Frame", bgrImage);
        cv::waitKey(0); // Keep the window open until a key is pressed
    }
    else
    {
        cout << "Failed to capture frame" << endl;
        return -1;
    }
    return 0;
}
