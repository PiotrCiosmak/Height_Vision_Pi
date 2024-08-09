# height-vision-pi/arm64:0.5.2
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
    libevent-dev \
    unzip

# Libcamera installation
RUN wget -O install_pivariety_pkgs.sh https://github.com/ArduCAM/Arducam-Pivariety-V4L2-Driver/releases/download/install_script/install_pivariety_pkgs.sh && \
    chmod +x install_pivariety_pkgs.sh && \
    sed -i 's/sudo //g' install_pivariety_pkgs.sh && \
    ./install_pivariety_pkgs.sh -p libcamera_dev && \
    ./install_pivariety_pkgs.sh -p libcamera_apps && \
    rm -r libcamera* rpicam* install_pivariety_pkgs.sh packages.txt

# OpenCV installation
RUN wget https://github.com/Qengineering/Install-OpenCV-Raspberry-Pi-64-bits/raw/main/OpenCV-4-10-0.sh && \
    chmod 755 ./OpenCV-4-10-0.sh && \
    sed -i 's/sudo //g' OpenCV-4-10-0.sh && \
    sed -i '/-D WITH_GSTREAMER=ON/a -D WITH_LIBCAMERA=ON \\' OpenCV-4-10-0.sh && \
    ./OpenCV-4-10-0.sh
RUN apt install -y \
    libopencv-dev

# GStreamer installation
RUN apt install -y \
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-bad \
    gstreamer1.0-plugins-ugly

WORKDIR /Height_Vision_Pi