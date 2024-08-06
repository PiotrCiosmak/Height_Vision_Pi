#include <iostream>
#include <libcamera/camera_manager.h>

int main()
{
    auto camera_manager{std::make_unique<libcamera::CameraManager>()};
    if (camera_manager->start())
    {
        std::cerr << "ERROR: Failed to start camera manager" << std::endl;
        exit(1);
    }

    auto cameras = camera_manager->cameras();
    if (cameras.empty())
    {
        std::cerr << "ERROR: No cameras found" << std::endl;
        exit(1);
    }



    camera_manager->stop();
}
