find_package(xtd REQUIRED)

project(jimoSDR)

add_sources(
    src/jimoSDR.cpp
    src/main_form.cpp
    src/properties_panel.cpp
    src/source_panel.cpp
    include/main_form.h
    include/properties_panel.h
    include/source_panel.h
    )


target_type(GUI_APPLICATION)

target_include_directories(jimoSDR PRIVATE include)
target_compile_features(jimoSDR PRIVATE cxx_std_20)