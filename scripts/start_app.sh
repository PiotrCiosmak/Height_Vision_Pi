#!/bin/bash

[[ ! -f "scripts/start_app.sh" ]] && echo "ERROR: Script must be run from main project directory" && exit 1
[[ "$#" -ne 0 ]] && echo "ERROR: Usage: $0" && exit 1

CONFIG_PATH="../config/config.json"
export CONFIG_PATH

rm -rf build
mkdir build
cd build || exit
cmake ..
make
./Height_Vision_Pi