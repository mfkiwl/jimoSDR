find_package(xtd REQUIRED)

find_package(SoapySDR REQUIRED)

#project(jimoSDR)

add_executable(jimoSDR
    src/jimoSDR.cpp
    src/main_form.cpp
    src/properties_panel.cpp
    src/user_draw_buttons.cpp
    src/source_dialog.cpp
    src/rtlsdr_properties_panel.cpp
    src/device_properties.cpp
    src/sampling_mode.cpp
    include/main_form.h
    include/properties_panel.h
    include/user_draw_buttons.h
    include/source_dialog.h
    include/rtlsdr_properties_panel.h
    include/device_properties.h
    include/exceptions.h
    include/sampling_mode.h
    )

target_include_directories(jimoSDR
    PUBLIC 
    include
    ../soapy/include
    ${SoapySDR_SOURCE_DIR}/include)

target_link_libraries(jimoSDR
    PRIVATE
    soapy
    SoapySDR
    xtd)

target_compile_features(jimoSDR PRIVATE cxx_std_20)