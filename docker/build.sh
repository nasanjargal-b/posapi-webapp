#!/bin/bash

cd $(dirname $0)

mkdir -p build && cd build && cmake -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - Unix Makefiles" ../../ && make

cd ..
cp ../build/posapi ./
cp ../webapp.ini ./

rm -r build

docker build -t nasanjargalb/posapi-webapp:$1 .