#!/bin/bash

[[ ! -f "scripts/run_docker.sh" ]] && echo "ERROR: Script must be run from main project directory" && exit 1

[[ "$#" -ne 0 && "$#" -ne 2 && "$#" -ne 3 ]] && echo "ERROR: Usage: $0 <ARCHITECTURE (x64 or arm64)> <IMAGE_VERSION> [start-app]" && exit 1

ARCHITECTURE=${1:-arm64}
[[ "$ARCHITECTURE" != "x64" && "$ARCHITECTURE" != "arm64" ]] && echo "ERROR: <ARCHITECTURE> must be x64 or arm64" && exit 1

VERSION=${2:-0.7.1}
IFS='.' read -r MAJOR MINOR PATCH <<< "$VERSION"
! [[ $MAJOR =~ ^[0-9]+$ ]] || ! [[ $MINOR =~ ^[0-9]+$ ]] || ! [[ $PATCH =~ ^[0-9]+$ ]] && echo "ERROR: <IMAGE_VERSION> must be in format NUMBER.NUMBER.NUMBER" && exit 1

START_APP=${3:-}
[[ -n "$START_APP" && "$START_APP" != "start-app" ]] && echo "ERROR: The third argument, if provided, must be 'start-app'" && exit 1

sudo xhost +Local:*

if [ "$START_APP" ]; then
    docker run --network host -it -v /run/udev:/run/udev -v $(pwd):/Height_Vision_Pi --privileged -e DISPLAY=${DISPLAY} ghcr.io/piotrciosmak/height-vision-pi/$ARCHITECTURE:$VERSION /bin/bash -c "chmod +x ./scripts/start_app.sh && ./scripts/start_app.sh"
else
    docker run --network host -it -v /run/udev:/run/udev -v $(pwd):/Height_Vision_Pi --privileged -e DISPLAY=${DISPLAY} --entrypoint /bin/bash ghcr.io/piotrciosmak/height-vision-pi/$ARCHITECTURE:$VERSION
fi