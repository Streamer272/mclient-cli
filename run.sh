#!/usr/bin/bash

meson build
cd build
ninja
src/mclient-cli
cd ..
rm -rf build

