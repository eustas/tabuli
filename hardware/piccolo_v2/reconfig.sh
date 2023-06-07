#!/bin/bash
export PICCOLO_ROOT=`pwd`
export PICO_SDK_PATH=`realpath ../../../pico-sdk`
export PICO_BOARD=pico
cd $PICO_SDK_PATH
git submodule update --init
cd $PICCOLO_ROOT

rm -rf ./build-device

cmake -B build-device ./uac2 -DCMAKE_EXPORT_COMPILE_COMMANDS=1
