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

    // Sprawdź aktualny format
    int fourcc = static_cast<int>(cap.get(cv::CAP_PROP_FOURCC));
    cout << "Current FourCC format: " << fourcc << endl;
    if (cap.read(frame))
    {
        cout << "Frame captured successfully." << endl;
        cout << "Frame size: " << frame.size() << endl;
        cout << "Frame type: " << frame.type() << endl;

        // Obsłuż format Bayera lub inny odpowiedni format
        if (frame.type() == CV_16UC1) // Sprawdź, czy to 16-bitowy obraz
        {
            cv::Mat bgrImage;
            cv::cvtColor(frame, bgrImage, cv::COLOR_BayerRG2BGR); // Dostosuj konwersję, jeśli używasz formatu Bayera

            // Wyświetl obraz
            imshow("Captured Frame", bgrImage);
            cv::waitKey(0); // Oczekuj na naciśnięcie klawisza
        }
        else
        {
            cout << "Unexpected frame format." << endl;
            return -1;
        }
    }
    else
    {
        cout << "Failed to capture frame" << endl;
        return -1;
    }

    return 0;
}