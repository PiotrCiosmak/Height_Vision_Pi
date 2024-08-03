# height-vision-pi/arm64:0.1.0
FROM arm64v8/debian:12

# Noninteractive package installation set
RUN DEBIAN_FRONTEND=noninteractive

# Time zone set
ENV TZ=Europe/Warsaw

# Libraries installation
RUN apt update && apt install -y \
    build-essential \
    cmake \
    git
