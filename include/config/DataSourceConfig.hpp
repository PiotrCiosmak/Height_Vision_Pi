#pragma once

#include <nlohmann/json.hpp>

namespace height_vision_pi
{
    enum DataSourceConfig
    {
        stream,
        none
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(DataSourceConfig,
                                 {
                                 {DataSourceConfig::stream, "stream"},
                                 {DataSourceConfig::none, "none"}
                                 })
}
