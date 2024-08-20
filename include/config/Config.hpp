#pragma once

#include "config/CameraConfig.hpp"
#include "config/DataSourceConfig.hpp"
#include "config/WindowConfig.hpp"

#include <string>
#include <mutex>

namespace height_vision_pi
{
    class Config
    {
    public:
        [[nodiscard]] static auto get() -> Config&;

        CameraConfig camera;
        DataSourceConfig data_source;
        WindowConfig window;

    private:
        Config() = default;
        Config(const Config&) = delete;
        Config& operator=(const Config&) = delete;
        void load(const std::string& file_path);

        static std::once_flag init_flag;
    };
}
