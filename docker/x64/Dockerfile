# height-vision-pi/x64:0.2.0
FROM ubuntu:latest

# Noninteractive package installation set
RUN DEBIAN_FRONTEND=noninteractive

# Time zone set
ENV TZ=Europe/Warsaw

# Libraries installation
RUN apt update && apt full-upgrade -y && apt install -y \
    build-essential \
    cmake \
    git \
    wget \
    pkg-config \
    libgtk2.0-dev \
    libevent-dev \
    unzip \
    libx264-dev \
    libjpeg-dev \
    libgstreamer1.0-dev \
    libgstreamer-plugins-base1.0-dev \
    libgstreamer-plugins-bad1.0-dev \
    gstreamer1.0-plugins-ugly \
    gstreamer1.0-tools \
    gstreamer1.0-gl \
    gstreamer1.0-gtk3 \
    libopencv-dev \
    libopencv-core4.5 \
    libopencv-imgproc4.5 \
    libopencv-highgui4.5 \
    libopencv-video4.5 \
    libboost-all-dev

# OpenCV installation
RUN git clone https://github.com/opencv/opencv.git -b master && \
    cd opencv && \
    mkdir build && \
    cd build && \
    cmake -D CMAKE_BUILD_TYPE=RELEASE \
      -D CMAKE_INSTALL_PREFIX=/usr/local \
      -D BUILD_opencv_java=OFF \
      -D BUILD_opencv_python=OFF \
      -D INSTALL_C_EXAMPLES=OFF \
      -D WITH_TBB=ON \
      -D ENABLE_FAST_MATH=1 \
      -D WITH_CUBLAS=1 \
      -D WITH_OPENGL=ON \
      -D WITH_GSTREAMER=ON \
      -D OPENCV_ENABLE_NONFREE=ON \
      -D WITH_GTK=ON \
      -D OPENCV_GENERATE_PKGCONFIG=ON \
    .. && \
    make -j$(nproc) && \
    make install

# Google Test installation
RUN git clone https://github.com/google/googletest.git /opt/googletest && \
    cd /opt/googletest && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make install

# Boost di installation
RUN git clone https://github.com/boost-experimental/di.git -b v1.3.0 /opt/boost-di

WORKDIR /Height_Vision_Pi