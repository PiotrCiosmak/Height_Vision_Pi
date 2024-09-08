cmake_minimum_required(VERSION 3.25.1)
project(Height_Vision_Pi)
set(CMAKE_CXX_STANDARD 23)

execute_process(
        COMMAND uname -m
        OUTPUT_VARIABLE SYSTEM_ARCHITECTURE
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

string(TOLOWER ${SYSTEM_ARCHITECTURE} SYSTEM_ARCHITECTURE)

if (SYSTEM_ARCHITECTURE STREQUAL "aarch64")
    add_definitions(-DAARCH64)
endif ()

find_package(PkgConfig REQUIRED)
find_package(OpenCV REQUIRED)
if (SYSTEM_ARCHITECTURE STREQUAL "aarch64")
    pkg_check_modules(LIBCAMERA REQUIRED libcamera)
endif ()
find_package(Boost REQUIRED COMPONENTS filesystem system)

option(ENABLE_TESTS "Build tests" ON)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${OpenCV_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS}
        /opt/boost-di/include
)

if (SYSTEM_ARCHITECTURE STREQUAL "aarch64")
    include_directories(
            ${LIBCAMERA_INCLUDE_DIRS}
    )
endif ()

set(HEIGHT_VISION_PI_SOURCES
        src/camera/DummyCameraController.cpp
        src/Injector.cpp
        src/config/Config.cpp
        src/Logger.cpp
        src/monitor/Monitor.cpp
        src/monitor/DummyMonitor.cpp
        src/monitor/utils/BashCommand.cpp
        src/detector/HumanDetector.cpp
)

if (SYSTEM_ARCHITECTURE STREQUAL "aarch64")
    list(APPEND HEIGHT_VISION_PI_SOURCES src/camera/ArduCamCameraController.cpp)
endif ()

add_library(HeightVisionPiSources ${HEIGHT_VISION_PI_SOURCES})

if (SYSTEM_ARCHITECTURE STREQUAL "aarch64")
    add_library(HeightVisionPiSources
            src/camera/ArduCamCameraController.cpp
    )
endif ()

target_link_libraries(HeightVisionPiSources
        ${OpenCV_LIBS}
        ${Boost_LIBRARIES}
)

if (SYSTEM_ARCHITECTURE STREQUAL "aarch64")
    target_link_libraries(HeightVisionPiSources
            ${LIBCAMERA_LIBRARIES}
    )
endif ()

add_executable(Height_Vision_Pi
        apps/main.cpp
)

target_link_libraries(Height_Vision_Pi
        HeightVisionPiSources
)

if (ENABLE_TESTS)
    add_subdirectory(tests)
endif ()