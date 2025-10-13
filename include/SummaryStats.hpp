#pragma once

#include <optional>
#include <vector>

namespace height_vision_pi
{
    class SummaryStats
    {
    public:
        SummaryStats() = default;

        void collectStats(int detected_humans,
                          int detected_faces,
                          const std::vector<std::optional<int>>& new_ages,
                          const std::vector<std::optional<double>>& new_heights);
        void display_and_save_summary_report() const;

    private:
        void addFrame();
        void addDetectedHuman(int count);
        void addDetectedFace(int count);
        void addCalculatedAge(const std::vector<std::optional<int>>& new_ages);
        void addCalculatedHeight(const std::vector<std::optional<double>>& new_heights);

        int total_frames;
        int humans_detected;
        int faces_detected;
        std::vector<int> ages;
        std::vector<double> heights;
    };
} // namespace height_vision_pi