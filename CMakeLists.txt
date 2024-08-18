cmake_minimum_required(VERSION 3.25.1)
project(Height_Vision_Pi)
set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
find_package(OpenCV REQUIRED)
pkg_check_modules(LIBCAMERA REQUIRED libcamera)

option(ENABLE_TESTS "Build tests" ON)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${LIBCAMERA_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
)

add_executable(Height_Vision_Pi
        apps/main.cpp
        src/camera/ArduCamCameraController.cpp
        src/camera/DummyCameraController.cpp
)

target_link_libraries(Height_Vision_Pi
        ${LIBCAMERA_LIBRARIES}
        ${OpenCV_LIBS}
)

if(ENABLE_TESTS)
    add_subdirectory(tests)
endif()