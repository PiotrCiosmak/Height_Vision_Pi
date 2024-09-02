add_executable(AllUnitTests
        camera/MockCameraControllerTests.cpp
        LoggerTests.cpp
        ../utils/mock/MockLogger.cpp
        MockLoggerTests.cpp
        monitor/MonitorTests.cpp
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