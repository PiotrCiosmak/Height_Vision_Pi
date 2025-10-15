#include "Injector.hpp"
#include "Logger.hpp"
#include "config/Config.hpp"
#include "SummaryStats.hpp"
#ifdef AARCH64
#include "camera/ArduCamCameraController.hpp"
#endif

#include <thread>

using namespace height_vision_pi;

namespace
{
    void logProcessingStart(int frame_number);
#ifdef AARCH64
    void showFrame(const cv::Mat& frame);
#else
    void saveFrame(const cv::Mat& frame);
#endif
    void logProcessingEnd(int& frame_number);
    void waitForNextFrame(const std::chrono::high_resolution_clock::time_point& start_time);
} // namespace

int main()
{
    auto stats = SummaryStats{};
#ifdef AARCH64
    const auto monitor = monitorInjector().create<std::unique_ptr<MonitorDevice>>();
#endif
    const auto camera_controller =
        cameraControllerInjector().create<std::unique_ptr<CameraController>>();
    const auto human_detector = humanDetectorInjector().create<std::unique_ptr<HumanDetector>>();
    const auto face_detector = faceDetectorInjector().create<std::unique_ptr<FaceDetector>>();
    const auto age_detector = ageDetectorInjector().create<std::unique_ptr<AgeDetector>>();
    const auto pupils_distance_calculator = pupilsDistanceCalculatorInjector().create<
        std::unique_ptr<PupilsDistanceCalculator>>();
    const auto height_calculator = heightCalculatorInjector().create<std::unique_ptr<
        HeightCalculator>>();
    static auto frame_number = 1;
    while (true)
    {
        const auto start_time = std::chrono::high_resolution_clock::now();
        logProcessingStart(frame_number);
#ifdef AARCH64
        monitor->check();
#endif
        auto frame = camera_controller->getFrame();
        if (!frame.empty())
        {
            const auto humans = human_detector->detect(frame);
            const auto faces = face_detector->detect(humans);
            const auto ages = age_detector->detect(faces);
            const auto distance_between_pupils = pupils_distance_calculator->
                calculate(faces);
            const auto heights = height_calculator->calculate(
                humans,
                faces,
                ages,
                distance_between_pupils);
            stats.collectStats(humans.size(),
                               faces.size(),
                               ages,
                               heights);
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

        logProcessingEnd(frame_number);
        waitForNextFrame(start_time);
    }
    stats.display_and_save_summary_report();
}

namespace
{
    void logProcessingStart(const int frame_number)
    {
        Logger::info("Start of processing frame no. {}", frame_number);
    }

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
        Logger::info("Main loop must wait: {} ms\n", sleep_duration);
        if (sleep_duration.count() > 0)
        {
            std::this_thread::sleep_for(sleep_duration);
        }
    }

    void logProcessingEnd(int& frame_number)
    {
        Logger::info("End of processing frame no. {}\n", frame_number++);
    }
} // namespace