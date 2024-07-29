# Height-Vision-PI/x64:0.0.2
FROM debian:12

# Noninteractive package installation set
RUN DEBIAN_FRONTEND=noninteractive

# Time zone set
ENV TZ=Europe/Warsaw

# Libraries installation
RUN apt update && apt install -y build-essential \
    cmake \
    git \
    gdb

# Google Test installation
RUN git clone https://github.com/google/googletest.git /googletest && \
    cd /googletest && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make install

