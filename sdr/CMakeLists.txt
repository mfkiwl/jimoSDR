cmake_minimum_required(VERSION 3.22)

find_package(SoapySDR REQUIRED)

add_library(sdr
    SHARED 
    src/Device.cpp
    src/Devices.cpp
    src/types.cpp
    include/Device.h
    include/Devices.h
    include/types.h)

    target_include_directories(sdr
        PUBLIC
        include
        ${SoapySDR_INCLUDE_DIRS})

    target_link_libraries(sdr
        PRIVATE
        SoapySDR)

    target_compile_features(sdr PRIVATE cxx_std_20)