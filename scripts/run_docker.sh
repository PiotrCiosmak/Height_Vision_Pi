#!/bin/bash

[[ ! -f "scripts/run_docker.sh" ]] && echo "ERROR: Script must be run from main project directory" && exit 1

[[ "$#" -ne 0 && "$#" -ne 2 ]] && echo "ERROR: Usage: $0 <ARCHITECTURE (x64 or arm64)> <IMAGE_VERSION>" && exit 1

ARCHITECTURE=${1:-arm64}
[[ "$ARCHITECTURE" != "x64" && "$ARCHITECTURE" != "arm64" ]] && echo "ERROR: <ARCHITECTURE> must be x64 or arm64" && exit 1

VERSION=${2:-0.7.1}
IFS='.' read -r MAJOR MINOR PATCH <<< "$VERSION"
! [[ $MAJOR =~ ^[0-9]+$ ]] || ! [[ $MINOR =~ ^[0-9]+$ ]] || ! [[ $PATCH =~ ^[0-9]+$ ]] && echo "ERROR: <IMAGE_VERSION> must be in format NUMBER.NUMBER.NUMBER" && exit 1

sudo xhost +Local:*

docker run --network host -it \
-v /run/udev:/run/udev \
-v $(pwd):/Height_Vision_Pi \
--device /dev/video0:/dev/video0 \
--device /dev/video1:/dev/video1 \
--device /dev/video2:/dev/video2 \
--device /dev/video3:/dev/video3 \
--device /dev/video4:/dev/video4 \
--device /dev/video5:/dev/video5 \
--device /dev/video6:/dev/video6 \
--device /dev/video7:/dev/video7 \
--device /dev/video19:/dev/video19 \
--device /dev/video20:/dev/video20 \
--device /dev/video21:/dev/video21 \
--device /dev/video22:/dev/video22 \
--device /dev/video23:/dev/video23 \
--device /dev/video24:/dev/video24 \
--device /dev/video25:/dev/video25 \
--device /dev/video26:/dev/video26 \
--device /dev/video27:/dev/video27 \
--device /dev/video28:/dev/video28 \
--device /dev/video29:/dev/video29 \
--device /dev/video30:/dev/video30 \
--device /dev/video31:/dev/video31 \
--device /dev/video32:/dev/video32 \
--device /dev/video33:/dev/video33 \
--device /dev/video34:/dev/video34 \
--device /dev/video35:/dev/video35 \
--device /dev/video36:/dev/video36 \
--device /dev/video37:/dev/video37 \
--device /dev/media0:/dev/media0 \
--device /dev/media1:/dev/media1 \
--device /dev/media2:/dev/media2 \
--device /dev/media3:/dev/media3 \
--device /dev/v4l-subdev0:/dev/v4l-subdev0 \
--device /dev/v4l-subdev1:/dev/v4l-subdev1 \
--device /dev/v4l-subdev2:/dev/v4l-subdev2 \
--device /dev/v4l-subdev3:/dev/v4l-subdev3 \
-e DISPLAY=${DISPLAY} \
--entrypoint /bin/bash ghcr.io/piotrciosmak/height-vision-pi/$ARCHITECTURE:$VERSION