#!/bin/bash
cmake --build build-device -j 16 && cp -v ./build-device/uac2.uf2 /Volumes/RPI-RP2/
