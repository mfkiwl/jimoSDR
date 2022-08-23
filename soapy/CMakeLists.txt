cmake_minimum_required(VERSION 3.22)

find_package(SoapySDR REQUIRED)

add_library(soapy
    SHARED 
    src/device.cpp
    src/devices.cpp
    include/device.h
    include/devices.h)

    target_include_directories(soapy
        PUBLIC
        include
        ${SoapySDR_INCLUDE_DIRS})

    target_link_libraries(soapy
        PRIVATE
        SoapySDR)

    target_compile_features(soapy PRIVATE cxx_std_20)