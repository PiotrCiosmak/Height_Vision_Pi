# height-vision-pi/x64:0.2.2
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
    libtbbmalloc2 \
    libtbb-dev \
    libatlas-base-dev \
    libblas-dev \
    liblapack-dev \
    libeigen3-dev \
    libopencv-dev \
    libboost-all-dev \
    gdb \
    nlohmann-json3-dev

# OpenCV installation
RUN git clone --depth 1 --branch 4.9.0 https://github.com/opencv/opencv_contrib.git && \
    git clone --depth 1 --branch 4.9.0 https://github.com/opencv/opencv.git && \
    cd opencv && \
    mkdir build && \
    cd build && \
    cmake .. \
      -D CMAKE_BUILD_TYPE=RELEASE \
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
      -D OPENCV_EXTRA_MODULES_PATH=/opencv_contrib/modules \
      -D WITH_GTK=ON \
    make && \
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