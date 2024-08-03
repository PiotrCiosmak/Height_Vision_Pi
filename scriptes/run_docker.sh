#!/bin/bash
ARCHITECTURE=${1:arm64}
VERSION=${2:0.1.0}
docker run --network host -it --device=/dev/video0 -v $(pwd):/Height_Vision_Pi --entrypoint /bin/bash ghcr.io/piotrciosmak/height-vision-pi/"$ARCHITECTURE":"$VERSION"