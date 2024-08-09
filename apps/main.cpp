#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
	// Przetestuj różne indeksy od 0 do 7
	for (int i = 0; i <= 7; ++i) {
		cv::VideoCapture cap(i,cv::CAP_V4L2);
		if (!cap.isOpened()) {
			std::cout << "Camera at index " << i << " is not opened." << std::endl;
			continue;
		}
		std::cout << "Camera at index " << i << " is opened." << std::endl;

		cv::Mat frame;
		cap >> frame;
		if (frame.empty()) {
			std::cerr << "Error: Frame is empty for camera index " << i << "!" << std::endl;
		} else {
			std::cout << "Captured frame from camera index " << i << std::endl;
			cv::imshow("Frame", frame);
			cv::waitKey(5000); // Wyświetl przez 5 sekund
		}

		cap.release();
	}

	return 0;
}
