#!/bin/bash

[[ ! -f "scripts/run_docker.sh" ]] && echo "ERROR: Script must be run from main project directory" && exit 1

[[ "$#" -ne 0 && "$#" -ne 2 ]] && echo "ERROR: Usage: $0 <ARCHITECTURE (x64 or arm64)> <IMAGE_VERSION>" && exit 1

ARCHITECTURE=${1:-arm64}
[[ "$ARCHITECTURE" != "x64" && "$ARCHITECTURE" != "arm64" ]] && echo "ERROR: <ARCHITECTURE> must be x64 or arm64" && exit 1

VERSION=${2:-0.7.1}
IFS='.' read -r MAJOR MINOR PATCH <<< "$VERSION"
! [[ $MAJOR =~ ^[0-9]+$ ]] || ! [[ $MINOR =~ ^[0-9]+$ ]] || ! [[ $PATCH =~ ^[0-9]+$ ]] && echo "ERROR: <IMAGE_VERSION> must be in format NUMBER.NUMBER.NUMBER" && exit 1

sudo xhost +Local:*

docker run --network host -it -v /run/udev:/run/udev -v $(pwd):/Height_Vision_Pi --device /dev/:/dev/ -e DISPLAY=${DISPLAY} --entrypoint /bin/bash ghcr.io/piotrciosmak/height-vision-pi/$ARCHITECTURE:$VERSION