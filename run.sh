#!/usr/bin/bash

meson build
cd build
ninja
src/out
cd ..
rm -rf build

