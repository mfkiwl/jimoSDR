find_package(xtd REQUIRED)

find_package(SoapySDR REQUIRED)

#project(jimoSDR)

add_executable(jimoSDR
    src/jimoSDR.cpp
    src/MainForm.cpp
    src/properties_panel.cpp
    src/user_draw_buttons.cpp
    src/source_dialog.cpp
    src/rtlsdr_properties_panel.cpp
    src/device_properties.cpp
    src/sampling_mode.cpp
    src/digit_incrementer.cpp
    src/number_display.cpp
    src/RadioReceiver.cpp
    include/MainForm.h
    include/properties_panel.h
    include/user_draw_buttons.h
    include/source_dialog.h
    include/rtlsdr_properties_panel.h
    include/device_properties.h
    include/exceptions.h
    include/sampling_mode.h
    include/digit_incrementer.h
    include/number_display.h
    include/ReceiverAction.h
    include/ReceiverTask.h
    include/RadioReceiver.h
    )

target_include_directories(jimoSDR
    PUBLIC 
    include
    ../set_directory_properties()/include
    ${SoapySDR_SOURCE_DIR}/include)

target_link_libraries(jimoSDR
    PRIVATE
    sdr
    SoapySDR
    xtd)

target_compile_features(jimoSDR PRIVATE cxx_std_20)