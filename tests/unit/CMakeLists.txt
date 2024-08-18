add_executable(AllUnitTests
        camera/CameraControllerTests.cpp
)

find_package(GTest REQUIRED)

target_include_directories(AllUnitTests PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/tests/utils
        ${GTEST_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(AllUnitTests
        GTest::gtest
        GTest::gmock
        GTest::gtest_main
        ${OpenCV_LIBS}
)

enable_testing()