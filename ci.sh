#!/bin/bash

set -e

clang-format -i $(git ls-files '*.cpp' '*.cc' '*.c' '*.h' '*.hpp')

cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
run-clang-tidy -p build