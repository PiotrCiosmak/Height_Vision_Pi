# height-vision-pi/x64:0.1.0
FROM debian:12

# Noninteractive package installation set
RUN DEBIAN_FRONTEND=noninteractive

# Time zone set
ENV TZ=Europe/Warsaw

# Libraries installation
RUN apt update && apt install -y \
    build-essential \
    cmake \
    git \
    gdb \
    wget


# Google Test installation
RUN git clone https://github.com/google/googletest.git /opt/googletest && \
    cd /opt/googletest && mkdir build && cd build && \
    cmake .. && make && make install

# Libcamera installation
RUN wget -O install_pivariety_pkgs.sh https://github.com/ArduCAM/Arducam-Pivariety-V4L2-Driver/releases/download/install_script/install_pivariety_pkgs.sh && \
    chmod +x install_pivariety_pkgs.sh && \
    sed -i 's/sudo //g' install_pivariety_pkgs.sh && \
    ./install_pivariety_pkgs.sh -p libcamera_dev && \
    ./install_pivariety_pkgs.sh -p libcamera_apps && \
     echo "dtoverlay=arducam-64mp,cam0" >> /boot/firmware/config.txt

WORKDIR /Height_Vision_Pi