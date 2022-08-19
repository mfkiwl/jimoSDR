find_package(xtd REQUIRED)

project(jimoSDR)

add_sources(
    src/jimoSDR.cpp
    )


target_type(GUI_APPLICATION)

target_compile_features(jimoSDR PRIVATE cxx_std_20)