# height-vision-pi/arm64:0.5.5
FROM dtcooper/raspberrypi-os:latest

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
    gstreamer1.0-gtk3

# Libcamera installation
RUN wget -O install_pivariety_pkgs.sh https://github.com/ArduCAM/Arducam-Pivariety-V4L2-Driver/releases/download/install_script/install_pivariety_pkgs.sh && \
    chmod +x install_pivariety_pkgs.sh && \
    sed -i 's/sudo //g' install_pivariety_pkgs.sh && \
    ./install_pivariety_pkgs.sh -p libcamera_dev && \
    ./install_pivariety_pkgs.sh -p libcamera_apps && \
    rm -r libcamera* rpicam* install_pivariety_pkgs.sh packages.txt

# OpenCV installation
RUN git clone https://github.com/advait-0/opencv.git -b libcamera-final && \
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
      -D WITH_LIBCAMERA=ON \
      -D WITH_GTK=ON \
      -D OPENCV_GENERATE_PKGCONFIG=ON \
    .. && \
    make -j$(nproc) && \
    make install

# Google Tests installation
RUN git clone https://github.com/google/googletest.git \
    cd googletest && \
    cmake . && \
    make && \
    make install

WORKDIR /Height_Vision_Pi