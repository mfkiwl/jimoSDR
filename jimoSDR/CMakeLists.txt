find_package(xtd REQUIRED)

find_package(SoapySDR REQUIRED)

#project(jimoSDR)

add_executable(jimoSDR
    src/jimoSDR.cpp
    src/main_form.cpp
    src/properties_panel.cpp
    src/source_panel.cpp
    src/rtlsdr_group_box.cpp
    src/user_draw_buttons.cpp
    include/main_form.h
    include/properties_panel.h
    include/source_panel.h
    include/rtlsdr_group_box.h
    include/user_draw_buttons.h
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