#include <libcamera/libcamera.h>
#include <iostream>
#include <memory>

using namespace libcamera;

class SimpleCameraApp
{
public:
    SimpleCameraApp()
    {
        cameraManager = std::make_unique<CameraManager>();
        if (cameraManager->start() != 0) {
            std::cerr << "Failed to start camera manager." << std::endl;
            return;
        }

        if (cameraManager->cameras().empty()) {
            std::cerr << "No cameras available." << std::endl;
            return;
        }

        camera = cameraManager->cameras()[0];
        if (!camera) {
            std::cerr << "Failed to acquire camera." << std::endl;
            return;
        }

        camera->acquire();
    }

    ~SimpleCameraApp()
    {
        if (camera)
            camera->release();
        cameraManager->stop();
    }

    void capture()
    {
        if (!camera) {
            std::cerr << "No camera available to capture." << std::endl;
            return;
        }

        // Tu możesz dodać kod konfigurujący strumienie i uruchamiający przechwytywanie obrazu
        std::cout << "Camera is ready to capture." << std::endl;
    }

private:
    std::unique_ptr<CameraManager> cameraManager;
    std::shared_ptr<Camera> camera;
};

int main()
{
    SimpleCameraApp app;
    app.capture();
    return 0;
}
