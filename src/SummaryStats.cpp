#include "SummaryStats.hpp"
#include "Logger.hpp"

#include <algorithm>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <optional>
#include <sstream>
#include <vector>

#include <boost/range/numeric.hpp>

using namespace height_vision_pi;

namespace
{
    const auto percent = [](const double part, const double total) -> double
    {
        return total > 0.0 ? (100.0 * part / total) : 0.0;
    };

    const auto average = [](const auto& values) -> double
    {
        return values.empty() ? 0.0 : boost::accumulate(values, 0.0) / values.size();
    };

    const auto minVal = [](const auto& values) -> double
    {
        return values.empty() ? 0.0 : *std::ranges::min_element(values);
    };

    const auto maxVal = [](const auto& values) -> double
    {
        return values.empty() ? 0.0 : *std::ranges::max_element(values);
    };
} // namespace

void SummaryStats::collectStats(const int detected_humans,
                                const int detected_faces,
                                const std::vector<std::optional<int>>& new_ages,
                                const std::vector<std::optional<double>>& new_heights)
{
    addFrame();
    addDetectedHuman(detected_humans);
    addDetectedFace(detected_faces);
    addCalculatedAge(new_ages);
    addCalculatedHeight(new_heights);
}

void SummaryStats::addFrame()
{
    total_frames++;
}

void SummaryStats::addDetectedHuman(const int count)
{
    humans_detected += count;
}

void SummaryStats::addDetectedFace(const int count)
{
    faces_detected += count;
}

void SummaryStats::addCalculatedAge(const std::vector<std::optional<int>>& new_ages)
{
    for (const auto& age : new_ages)
    {
        if (age.has_value())
        {
            ages.push_back(age.value());
        }
    }
}

void SummaryStats::addCalculatedHeight(const std::vector<std::optional<double>>& new_heights)
{
    for (const auto& height : new_heights)
    {
        if (height.has_value())
        {
            heights.push_back(height.value());
        }
    }
}

void SummaryStats::display_and_save_summary_report() const
{
    const auto human_detected_percent = percent(humans_detected, total_frames);
    const auto face_detected_percent = percent(faces_detected, humans_detected);
    const auto age_detected_percent = percent(ages.size(), humans_detected);
    const auto height_detected_percent = percent(heights.size(), humans_detected);

    const auto average_age = average(ages);
    const auto min_age = minVal(ages);
    const auto max_age = maxVal(ages);
    const auto average_height = average(heights);
    const auto min_height = minVal(heights);
    const auto max_height = maxVal(heights);

    Logger::info("==================================================");
    Logger::info("📊 SUMMARY REPORT");
    Logger::info("==================================================");
    Logger::info("🧍 Human detected in:         {}% of frames", human_detected_percent);
    Logger::info("🙂 Face detected for:         {}% of humans", face_detected_percent);
    Logger::info("🎂 Age estimated for:         {}% of humans", age_detected_percent);
    Logger::info("   ├─ Average age:            {} years", average_age);
    Logger::info("   ├─ Minimum age:            {} years", min_age);
    Logger::info("   └─ Maximum age:            {} years", max_age);
    Logger::info("📏 Height estimated for:      {}% of humans", height_detected_percent);
    Logger::info("   ├─ Average height:         {} cm", average_height);
    Logger::info("   ├─ Minimum height:         {} cm", min_height);
    Logger::info("   └─ Maximum height:         {} cm", max_height);
    Logger::info("==================================================\n");

    std::filesystem::create_directories("reports");

    const auto file_name = []
    {
        std::ostringstream ss;
        const auto now = std::time(nullptr);
        ss << "reports/" << std::put_time(std::localtime(&now), "%Y-%m-%d_%H-%M-%S") << ".txt";
        return ss.str();
    }();

    auto file = std::ofstream{file_name};
    if (file.is_open())
    {
        file << "SUMMARY REPORT\n"
            << "-----------------------------\n"
            << "Human detected: " << human_detected_percent << "%\n"
            << "Face detected: " << face_detected_percent << "%\n"
            << "Age detected: " << age_detected_percent << "%\n"
            << "Average age: " << average_age << "\n"
            << "Min age: " << min_age << "\n"
            << "Max age: " << max_age << "\n"
            << "Height detected: " << height_detected_percent << "%\n"
            << "Average height: " << average_height << "\n"
            << "Min height: " << min_height << "\n"
            << "Max height: " << max_height << "\n";

        Logger::info("Summary saved to file: {}", file_name);
    }
    else
    {
        Logger::error("Could not write summary file: {}", file_name);
    }
}