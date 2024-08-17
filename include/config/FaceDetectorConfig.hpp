#pragma once

#include <string>

struct FaceDetectorConfig
{
    std::string classifier_path;
    double scale_factor;
    int min_neighbors;
    int flags;
    int min_width;
    int min_height;
};
