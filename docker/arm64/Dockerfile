# height-vision-pi/arm64:0.6.0
FROM dtcooper/raspberrypi-os:latest

# Noninteractive package installation set
RUN DEBIAN_FRONTEND=noninteractive

# Time zone set
ENV TZ=Europe/Warsaw

# Dependencies for OpenCV
RUN apt update && apt full-upgrade -y && apt install -y \
    libgtk2.0-dev \
    build-essential \
    cmake \
    git \
    pkg-config \
    libgtk-3-dev \
    libavcodec-dev \
    libavformat-dev \
    libswscale-dev \
    libv4l-dev \
    libxvidcore-dev \
    libx264-dev \
    libjpeg-dev \
    libpng-dev \
    libtiff-dev \
    gfortran \
    openexr \
    libatlas-base-dev \
    python3-dev \
    python3-numpy \
    libtbb2 \
    libtbb-dev \
    libdc1394-22-dev \
    libopenexr-dev \
    libgstreamer-plugins-base1.0-dev \
    libgstreamer1.0-dev

# OpenCV
RUN git clone https://github.com/advait-0/opencv.git && \
    cd opencv && \
    mkdir build && cd build && \
    cmake -D CMAKE_BUILD_TYPE=RELEASE \
      -D CMAKE_INSTALL_PREFIX=/usr/local \
      -D INSTALL_C_EXAMPLES=ON \
      -D INSTALL_PYTHON_EXAMPLES=ON \
      -D WITH_LIBCAMERA=ON \
      -D OPENCV_GENERATE_PKGCONFIG=ON \
      -D BUILD_EXAMPLES=ON .. && \
    make -j4 && \
    make install

# Dependencies for libcamera
RUN apt install -y \
    meson \
    ninja-build \
    libyaml-dev \
    python3-yaml \
    python3-ply \
    python3-jinja2 \
    libgnutls28-dev \
    libudev-dev \
    qtbase5-dev \
    qttools5-dev-tools \
    libpython3-dev \
    pybind11-dev \
    libevent-dev

# Libcamera
RUN git clone https://git.libcamera.org/libcamera/libcamera.git && \
    cd libcamera && \
    meson setup build && \
    ninja -C build install

WORKDIR /Height_Vision_Pi