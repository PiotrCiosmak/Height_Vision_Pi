#include <camera/CameraController.hpp>

#include <gmock/gmock.h>

//TODO whole
using namespace height_vision_pi;

class MockVideoCapture : public CameraController
{
public:
    MOCK_METHOD(bool, open, (int device), (override));
    MOCK_METHOD(bool, isOpened, (), (const, override));
    MOCK_METHOD(bool, read, (cv::Mat frame), (override));
    MOCK_METHOD(bool, set, (int propId, double value), (override));
};