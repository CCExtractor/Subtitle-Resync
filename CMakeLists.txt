cmake_minimum_required(VERSION 3.14)
project(Subtitle_Resync)

set(CMAKE_CXX_STANDARD 14)

add_executable(Subtitle_Resync src/main.cpp src/subtitle_resync.cpp src/subtitle_resync.h src/utils/dactylogram.cpp src/utils/dactylogram.h src/utils/base64_strings.cpp src/utils/base64_strings.h src/utils/align_fingerprints.cpp src/utils/align_fingerprints.h)