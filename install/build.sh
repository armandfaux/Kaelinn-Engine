#!/bin/bash

if [ -d "build" ]; then
  rm -rf build
fi

usage() {
  echo "Usage: $0 --game <game_name> [--linter <linter_name>] [--download] [--tests]"
  exit 1
}

if [ "$#" -eq 0 ]; then
  usage
fi

options=$(getopt -o "" -l "game:,linter:,download,tests" -n "$0" -- "$@")
if [ $? -ne 0 ]; then
  usage
fi
eval set -- "$options"

game_name=""
download=false
os_name=""

command="cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release"
while true; do
    case "$1" in
        --game)
            game_name="$2"
            command+=" -DENABLE_PROJECT=$2"
            shift 2
            ;;
        --linter)
            command+=" -DACTIVATE_LINTER=$2"
            shift 2
            ;;
        --download)
            download=true
            shift
            ;;
        --tests)
            command+=" -DENABLE_TESTS=true"
            shift
            ;;
        --)
            shift
            break
            ;;
        *)
            usage
            ;;
    esac
done
if [ -z "$game_name" ]; then
  usage
fi

if [ "$os_name" == "Darwin" ];then
    echo "MacOS detected: $os_name"
    num_cores=$(sysctl -n hw.ncpu)
else
    echo "Linux detected: $os_name"
    num_cores=$(nproc)
fi

echo "Building with $num_cores cores"

conan profile detect --force
conan install . --output-folder=build --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True
cd build
eval "$command"
cmake --build . -- -j"$num_cores"

if [ $download == true ]; then
    cpack
fi