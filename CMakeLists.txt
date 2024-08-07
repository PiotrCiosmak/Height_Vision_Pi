cmake_minimum_required(VERSION 3.25.1)
project(Height_Vision_Pi)
set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
find_package(OpenCV REQUIRED)
pkg_check_modules(LIBCAMERA REQUIRED libcamera)
pkg_check_modules(LIBEVENT REQUIRED IMPORTED_TARGET libevent_pthreads)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${LIBCAMERA_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${LIBEVENT_INCLUDE_DIRS}
)

add_executable(Height_Vision_Pi
        apps/main.cpp
        src/camera/CameraManagerWrapper.cpp
        event_loop.cpp
)

target_link_libraries(Height_Vision_Pi
        ${LIBCAMERA_LIBRARIES}
        ${OpenCV_LIBS}
        PkgConfig::LIBEVENT
)