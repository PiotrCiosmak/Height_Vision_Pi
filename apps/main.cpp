#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
	cv::VideoCapture cap(0); // 0 oznacza domyślny aparat

	if (!cap.isOpened()) {
		std::cerr << "Error: Camera not found!" << std::endl;
		return -1;
	}
	int imageCount = 0;
	cv::Mat frame;
	while (true) {
		cap >> frame;
		if (frame.empty()) break;

		std::string filename = "frame_" + std::to_string(imageCount++) + ".jpg";
		cv::imwrite(filename, frame);
		std::cout << "Saved: " << filename << std::endl;
		if (cv::waitKey(30) >= 0) break;
	}

	return 0;
}
