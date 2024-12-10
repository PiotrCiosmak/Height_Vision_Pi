add_executable(AllUnitTests
        camera/MockCameraControllerTest.cpp
        LoggerTest.cpp
        ../utils/mock/MockLogger.cpp
        MockLoggerTest.cpp
        monitor/MockMonitorTest.cpp
        detector/HumanDetectorTest.cpp
        detector/FaceDetectorTest.cpp
        detector/AgeDetectorTest.cpp
)

find_package(GTest REQUIRED)

target_include_directories(AllUnitTests PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/tests/utils
        ${GTEST_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS}
        /opt/boost-di/include
)

set(MODELS_DIR "${PROJECT_SOURCE_DIR}/models")
set(RESOURCES_DIR "${PROJECT_SOURCE_DIR}/resources")
set(CONFIG_DIR "${PROJECT_SOURCE_DIR}/config")

add_definitions(
        -DMODELS_DIR="${MODELS_DIR}"
        -DRESOURCES_DIR="${RESOURCES_DIR}"
        -DCONFIG_DIR="${CONFIG_DIR}"
)

target_link_libraries(AllUnitTests
        HeightVisionPiSources
        GTest::gtest
        GTest::gmock
        GTest::gtest_main
        ${OpenCV_LIBS}
        ${Boost_LIBRARIES}
)

enable_testing()
add_test(NAME AllUnitTests COMMAND AllUnitTests)