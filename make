#!/bin/bash
while getopts 'd' OPTION; do
  case "$OPTION" in
    d)
      echo "Making a Debug version with NO optimizations"
      cmake -DCMAKE_BUILD_TYPE=Debug -S. -Bbuild && cmake --build build
      exit
      ;;
    dd)
      echo "Making a Release version with debug symbols"
      cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -S. -Bbuild && cmake --build build
      exit
      ;;
    ?)
      ;;
  esac
done
shift "$(($OPTIND -1))"
cmake -S. -Bbuild && cmake --build build
