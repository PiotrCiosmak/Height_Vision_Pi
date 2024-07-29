# Height-Vision-PI/arm64:0.0.1
FROM arm64v8/debian:12

# Noninteractive package installation set
RUN DEBIAN_FRONTEND=noninteractive

# Time zone set
ENV TZ=Europe/Warsaw

# Libraries installation
RUN apt update && apt install build-essential \
    cmake

