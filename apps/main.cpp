#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main() {

    VideoCapture cap(0, CAP_V4L2);
    if (!cap.isOpened()) {
        cout << "Cannot open camera\n";
        return -1;
    }

    Mat frame;
    namedWindow("Camera Feed", WINDOW_AUTOSIZE); // Tworzymy okno do wyświetlania obrazu

    while (true) {
        bool ret = cap.read(frame);
        if (!ret) {
            cout << "Error. Failed to receive frame.\n";
            break;
        }

        imshow("Camera Feed", frame); // Wyświetlamy klatkę w oknie

        if (waitKey(1) == 'q') { // Sprawdzamy, czy naciśnięto 'q'
            break;
        }
    }

    cap.release(); // Zwolnienie zasobów kamery
    destroyAllWindows(); // Zamknięcie wszystkich okien OpenCV

    return 0;
}
