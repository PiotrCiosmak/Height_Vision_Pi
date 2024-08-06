// Opencv needs to be installed on your Raspberry Pi
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main() {
    VideoCapture cap(0,CAP_V4L2);
    if (!cap.isOpened()) {
        cout << "Cannot open camera\n";
        return -1;
    }

    Mat frame;
    while (true) {
        bool ret = cap.read(frame);
        if (!ret) {
            cout << "Error. Fail to receive frame.\n";
            break;
        }
        if (waitKey(1) == 'q') {
            break;
        }
    }

    return 0;
}
