#include <opencv2/opencv.hpp>
#include <iostream>
#include <libcamera/formats.h>

using namespace std;
using namespace cv;

int main() {
    // Inicjalizacja obiektu VideoCapture
    VideoCapture cap(0, libcamera::formats::NV12); // Używa domyślnego backendu dla kamery

    if (!cap.isOpened()) {
        cout << "Cannot open camera\n";
        return -1;
    }

    Mat frame;
    if (cap.read(frame)) { // Próbuj odczytać jedną klatkę
        // Zapisz klatkę do pliku
        bool success = imwrite("captured_frame.jpg", frame); // Zapisuje obraz do pliku "captured_frame.jpg"
        if (!success) {
            cout << "Error: Failed to save the frame.\n";
        } else {
            cout << "Frame saved as 'captured_frame.jpg'.\n";
        }
    } else {
        cout << "Error: Failed to capture frame.\n";
    }

    cap.release(); // Zwolnienie zasobów kamery
    return 0;
}
