#include "calculator/PupilsDistanceCalculator.hpp"
#include "Logger.hpp"

using namespace height_vision_pi;

auto PupilsDistanceCalculator::calculate(
    const std::vector<cv::Mat>& detected_faces) -> std::vector<std::optional<double>>
{
    auto distances = std::vector<std::optional<double>>{};

    for (const auto& face : detected_faces)
    {
        if (face.empty())
        {
            distances.emplace_back(std::nullopt);
            continue;
        }

        const auto face_roi = preprocessFace(face);

        const auto eye_width = face_roi.cols / 4;
        const auto eye_height = face_roi.rows / 4;

        constexpr auto right_eye_x_ratio = 0.3;
        constexpr auto right_eye_y_ratio = 0.0;
        constexpr auto left_eye_x_ratio = 0.7;
        constexpr auto left_eye_y_ratio = 0.4;

        const auto right_eye_rect = getEyeRect(face_roi,
                                               right_eye_x_ratio,
                                               right_eye_y_ratio,
                                               eye_width,
                                               eye_height);
        const auto left_eye_rect = getEyeRect(face_roi,
                                              left_eye_x_ratio,
                                              left_eye_y_ratio,
                                              eye_width,
                                              eye_height);

        auto right_pupil_position = findEyeCenterInROI(face_roi(right_eye_rect));
        auto left_pupil_position = findEyeCenterInROI(face_roi(left_eye_rect));

        right_pupil_position = adjustPupilPosition(right_pupil_position, right_eye_rect);
        left_pupil_position = adjustPupilPosition(left_pupil_position, left_eye_rect);

        const auto distance = calculateDistanceBetweenPupils(
            right_pupil_position,
            left_pupil_position);

        distances.push_back(distance);
    }

    const auto calculated_pupils_distance_count = std::ranges::count_if(distances,
        [](const auto& distance)
        {
            return distance.has_value();
        });

    Logger::info("{} out of {} possible pupils distance calculated",
                 calculated_pupils_distance_count,
                 distances.size());

    return distances;
}

auto PupilsDistanceCalculator::preprocessFace(const cv::Mat& face) -> cv::Mat
{
    const auto min_side_length = std::min(face.cols, face.rows);
    const auto blur_sigma = 0.005 * min_side_length;
    auto face_roi = face.clone();
    cv::GaussianBlur(face_roi, face_roi, cv::Size(0, 0), blur_sigma);
    return face_roi;
}

auto PupilsDistanceCalculator::getEyeRect(const cv::Mat& face_roi,
                                          const double ratio_x,
                                          const double ratio_y,
                                          const int eye_width,
                                          const int eye_height) -> cv::Rect
{
    auto eye_x = static_cast<int>(face_roi.cols * ratio_x) - eye_width / 2;
    auto eye_y = static_cast<int>(face_roi.rows * ratio_y) - eye_height / 2;
    eye_x = std::max(0, eye_x);
    eye_y = std::max(0, eye_y);
    auto eye_rect = cv::Rect{eye_x, eye_y, eye_width, eye_height};
    eye_rect &= cv::Rect(0, 0, face_roi.cols, face_roi.rows);
    return eye_rect;
}

auto PupilsDistanceCalculator::findEyeCenterInROI(const cv::Mat& eye_roi) -> cv::Point
{
    auto eye_roi_gray = cv::Mat{};
    if (eye_roi.channels() == 3)
    {
        cv::cvtColor(eye_roi, eye_roi_gray, cv::COLOR_BGR2GRAY);
    }
    else
    {
        eye_roi_gray = eye_roi;
    }

    const auto gradient_x = cv::Mat{computeMatXGradient(eye_roi_gray)};
    const auto gradient_y = cv::Mat{computeMatXGradient(eye_roi_gray.t()).t()};

    auto gradient_magnitude = cv::Mat{};
    cv::magnitude(gradient_x, gradient_x, gradient_magnitude);

    const auto mean = cv::Scalar{};
    const auto std_dev = cv::Scalar{};
    cv::meanStdDev(gradient_magnitude, mean, std_dev);
    const auto magnitude_threshold = 0.3 * std_dev[0] + mean[0];

    auto score_map = cv::Mat{cv::Mat::zeros(eye_roi_gray.size(), CV_64F)};

    for (int y = 0; y < eye_roi_gray.rows; ++y)
    {
        for (int x = 0; x < eye_roi_gray.cols; ++x)
        {
            const auto current_gradient_magnitude = gradient_magnitude.at<double>(y, x);
            if (current_gradient_magnitude < magnitude_threshold)
            {
                continue;
            }

            const auto normalized_gradient_x =
                gradient_x.at<double>(y, x) / current_gradient_magnitude;
            const auto normalized_gradient_y =
                gradient_y.at<double>(y, x) / current_gradient_magnitude;

            for (int candidate_y = 0; candidate_y < eye_roi_gray.rows; ++candidate_y)
            {
                for (int candidate_x = 0; candidate_x < eye_roi_gray.cols; ++candidate_x)
                {
                    const auto delta_x = candidate_x - x;
                    const auto delta_y = candidate_y - y;
                    const auto distance = std::sqrt(std::pow(delta_x, 2) + std::pow(delta_y, 2));
                    constexpr auto min_distance = 1e-5;
                    if (distance < min_distance)
                    {
                        continue;
                    }
                    const auto direction_x = delta_x / distance;
                    const auto direction_y = delta_y / distance;
                    auto dot_product = normalized_gradient_x * direction_x + normalized_gradient_y *
                                       direction_y;
                    dot_product = std::max(0.0, dot_product);
                    score_map.at<double>(candidate_y, candidate_x) += dot_product * dot_product;
                }
            }
        }
    }

    double max_value = {};
    auto eye_center = cv::Point{};
    cv::minMaxLoc(score_map, nullptr, &max_value, nullptr, &eye_center);
    return eye_center;
}

auto PupilsDistanceCalculator::computeMatXGradient(const cv::Mat& src) -> cv::Mat
{
    auto gradient = cv::Mat(src.rows, src.cols, CV_64F);

    for (int row_index = 0; row_index < src.rows; ++row_index)
    {
        gradient.at<double>(row_index, 0) =
            static_cast<double>(src.at<unsigned char>(row_index, 1)) - src.at<
                unsigned char>(row_index, 0);

        for (int col_index = 1; col_index < src.cols - 1; ++col_index)
        {
            gradient.at<double>(row_index, col_index) = (static_cast<double>(src.at<unsigned char>(
                                                             row_index,
                                                             col_index + 1)) -
                                                         static_cast<double>(src.at<unsigned char>(
                                                             row_index,
                                                             col_index - 1))) / 2.0;
        }
        gradient.at<double>(row_index, src.cols - 1) =
            static_cast<double>(src.at<unsigned char>(row_index, src.cols - 1)) - src.at<unsigned
                char>(row_index, src.cols - 2);
    }

    return gradient;
}

auto PupilsDistanceCalculator::adjustPupilPosition(const cv::Point& pupil_position,
                                                   const cv::Rect& eye_rect) -> cv::Point
{
    return cv::Point{pupil_position.x + eye_rect.x, pupil_position.y + eye_rect.y};
}

auto PupilsDistanceCalculator::calculateDistanceBetweenPupils(
    const cv::Point& right_pupil_position,
    const cv::Point& left_pupil_position) -> double
{
    return std::sqrt(
        std::pow(right_pupil_position.x - left_pupil_position.x, 2) + std::pow(
            left_pupil_position.y - right_pupil_position.y,
            2));
}