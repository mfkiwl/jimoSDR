find_package(xtd REQUIRED)

find_package(SoapySDR REQUIRED)

#project(jimoSDR)

add_executable(jimoSDR
    src/jimoSDR.cpp
    src/main_form.cpp
    src/properties_panel.cpp
    src/source_panel.cpp
    include/main_form.h
    include/properties_panel.h
    include/source_panel.h
    )

target_include_directories(jimoSDR
    PUBLIC 
    include
    ${SoapySDR_SOURCE_DIR}/include)

target_link_libraries(jimoSDR
    PRIVATE
    SoapySDR
    xtd)

target_compile_features(jimoSDR PRIVATE cxx_std_20)