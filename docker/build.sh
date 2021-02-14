#!/bin/bash

cd $(dirname $0)

mkdir -p build && cd build && cmake -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - Unix Makefiles" ../../ && make

cd ..
cp ../build/posapi ./
cp ../conf.ini ./
cp ../lib/libPosAPI.so ./

docker build -t nasanjargalb/posapi-webapp:$1 .

rm -r build/ conf.ini posapi lib*