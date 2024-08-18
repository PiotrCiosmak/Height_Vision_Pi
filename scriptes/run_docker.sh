#!/bin/bash
ARCHITECTURE=${1:-arm64}
VERSION=${2:-0.7.0}

sudo xhost +Local:*

docker run --network host -it -v /run/udev:/run/udev -v $(pwd):/Height_Vision_Pi --privileged -e DISPLAY=${DISPLAY} --entrypoint /bin/bash ghcr.io/piotrciosmak/height-vision-pi/$ARCHITECTURE:$VERSION