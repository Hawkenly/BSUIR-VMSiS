cmake_minimum_required(VERSION 3.26)
project(ntfs_checker)

set(CMAKE_CXX_STANDARD 17)
#[[set(CMAKE_EXE_LINKER_FLAGS "-static")]]
add_executable(ntfs_checker main.cpp
        runList.cpp
        processRecord.cpp
        analysis.cpp
        )
