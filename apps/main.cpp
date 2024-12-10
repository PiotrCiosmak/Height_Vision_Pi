#include "Injector.hpp"
#include "Logger.hpp"
#include "config/Config.hpp"
#ifdef AARCH64
#include "camera/ArduCamCameraController.hpp"
#endif

#include <thread>

using namespace height_vision_pi;

namespace
{
    void saveFrame(const cv::Mat& frame);
#ifdef AARCH64
    void showFrame(const cv::Mat& frame);
#endif
    void waitForNextFrame(const std::chrono::high_resolution_clock::time_point& start_time);
} // namespace

int main()
{
#ifdef AARCH64
    const auto monitor = monitorInjector().create<std::unique_ptr<MonitorDevice>>();
#endif
    const auto camera_controller =
        cameraControllerInjector().create<std::unique_ptr<CameraController>>();
    const auto human_detector = humanDetectorInjector().create<std::unique_ptr<HumanDetector>>();
    const auto face_detector = faceDetectorInjector().create<std::unique_ptr<FaceDetector>>();
    const auto age_detector = ageDetectorInjector().create<std::unique_ptr<AgeDetector>>();
    while (true)
    {
        const auto start_time = std::chrono::high_resolution_clock::now();

#ifdef AARCH64
        monitor->check();
#endif

        auto frame = camera_controller->getFrame();
        if (!frame.empty())
        {
            const auto detected_humans = human_detector->detect(frame);
            const auto detected_faces = face_detector->detect(detected_humans);
            [[maybe_unused]] const auto detected_ages = age_detector->detect(detected_faces);
            // TODO Calculate the distance between the pupils
            // TODO Calculate height based on age and distance between the pupils
#ifdef AARCH64
            showFrame(frame);
#else
            saveFrame(frame);
#endif
        }

        if (cv::waitKey(1) == 'q')
        {
            break;
        }

        waitForNextFrame(start_time);
    }
}

namespace
{
#ifdef AARCH64
    void showFrame(const cv::Mat& frame)
    {
        imshow(Config::get().window.name, frame);
        cv::resizeWindow(Config::get().window.name,
                         Config::get().camera.resolution.x,
                         Config::get().camera.resolution.y);
    }
#else
    void saveFrame(const cv::Mat& frame)
    {
        static auto frame_counter = 0;
        auto filename = std::ostringstream{};
        filename << "frame_" << std::setw(4) << std::setfill('0') << frame_counter++ << ".png";
        cv::imwrite(filename.str(), frame);
    }
#endif

    void waitForNextFrame(const std::chrono::high_resolution_clock::time_point& start_time)
    {
        const auto frame_duration =
            std::chrono::milliseconds{1000 / static_cast<int>(Config::get().camera.fps)};
        const auto end_time = std::chrono::high_resolution_clock::now();
        const auto elapsed_time = end_time - start_time;
        const auto sleep_duration =
            frame_duration - std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time);
        Logger::info("Main loop must wait: {} ms", sleep_duration);
        if (sleep_duration.count() > 0)
        {
            std::this_thread::sleep_for(sleep_duration);
        }
    }
} // namespace