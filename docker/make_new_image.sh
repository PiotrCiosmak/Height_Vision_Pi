#!/bin/bash

[[ ! -f "docker/make_new_image.sh" ]] && echo "ERROR: Script must be run from main project directory" && exit 1

[[ "$#" -ne 2 ]] && echo "ERROR: Usage: $0 <IMAGE_VERSION> <ARCHITECTURE (x64 or arm64)>" && exit 1

IMAGE_VERSION="$1"
IFS='.' read -r MAJOR MINOR PATCH <<< "$IMAGE_VERSION"
! [[ $MAJOR =~ ^[0-9]+$ ]] || ! [[ $MINOR =~ ^[0-9]+$ ]] || ! [[ $PATCH =~ ^[0-9]+$ ]] && echo "ERROR: <IMAGE_VERSION> must be in format NUMBER.NUMBER.NUMBER" && exit 1

ARCHITECTURE="$2"
[[ "$ARCHITECTURE" != "x64" && "$ARCHITECTURE" != "arm64" ]] && echo "ERROR: <ARCHITECTURE> must be x64 or arm64" && exit 1

IMAGE_NAME="ghcr.io/piotrciosmak/height-vision-pi/$ARCHITECTURE:$IMAGE_VERSION"

if [[ "$ARCHITECTURE" == "arm64" ]]; then
  docker buildx build --platform linux/arm64 \
    -t "$IMAGE_NAME" \
    -f ./docker/"$ARCHITECTURE"/Dockerfile \
    --progress=plain \
    . >>docker_build.log
else
  docker build \
    -t "$IMAGE_NAME" \
    -f ./docker/"$ARCHITECTURE"/Dockerfile \
    --progress=plain \
    . >>docker_build.log
fi

docker push "$IMAGE_NAME"