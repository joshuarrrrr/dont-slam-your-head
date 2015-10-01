#!/bin/sh

ANDROID_NDK=${1:-"/opt/android-sdk/ndk-bundle"}
ANDROID_ABI=${2:-"armeabi-v7a with NEON"}
EIGEN_DIR=${3:-"/usr/include/eigen3"}

echo "using android-ndk:       $ANDROID_NDK"
echo "using android abi:       $ANDROID_ABI"
echo "using eigen include dir: $EIGEN_DIR"

# get directory of script and cd to its parent
DIR="$( cd "$( dirname "$0" )" && pwd )"
cd $DIR/..

# no build directory, create it
if [[ ! -d "android-build" ]]; then
    mkdir android-build
fi

cd android-build

# no makefile in build dir, run cmake
if [[ ! -f "Makefile" ]]; then
  cmake -DCMAKE_TOOLCHAIN_FILE=../utils/android-cmake/android.toolchain.cmake \
  	-DANDROID_NDK=${ANDROID_NDK} \
  	-DCMAKE_BUILD_TYPE=Release \
  	-DANDROID_ABI=${ANDROID_ABI} \
  	-DEIGEN3_INCLUDE_DIR=${EIGEN_DIR} \
  	-DEIGEN3_VERSION_OK=ON ..
fi

# build it
cmake --build .
