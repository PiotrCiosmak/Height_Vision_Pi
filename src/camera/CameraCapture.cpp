#include "camera/CameraCapture.hpp"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <libcamera/libcamera.h>
#include <libcamera/stream.h>
#include <libcamera/camera_manager.h>
#include <libcamera/camera.h>

using namespace height_vision_pi;

CameraCapture::CameraCapture(): camera_manager_wrapper{}
{
}

void CameraCapture::startCapture()
{
    auto cameras = camera_manager_wrapper.getCameras();
    if (cameras.empty())
    {
        std::cerr << "ERROR: No cameras found" << std::endl;
        exit(1);
    }
    auto camera = cameras.front();

    if(camera->acquire())
    {
        std::cerr<<"ERROR: Failed to acquire camera"<<std::endl;
        exit(1);
    }

    auto config = camera->generateConfiguration({libcamera::StreamRole::VideoRecording});
    if(!config)
    {
        std::cerr<<"ERROR: Failed to generate configuration"<<std::endl;
        camera->release();
        exit(1);
    }

    config->at(0).pixelFormat = libcamera::formats::YUV420;
    config->at(0).size.width = 1920;
    config->at(0).size.height = 1080;

    config->validate();
    if(camera->configure(config.get()))
    {
        std::cerr<<"ERROR: Failed to confgure camera"<<std::endl;
        camera->release();
        exit(1);
    }

    if(camera->start())
    {
        std::cerr<<"ERROR: Failed to start camera"<<std::endl;
    }

    std::cout<<"CHYBA DZIAŁAM\n";

    cv::destroyAllWindows();

    camera->stop();
    camera->release();
}

