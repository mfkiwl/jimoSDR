find_package(xtd REQUIRED)

find_package(SoapySDR REQUIRED)

#project(jimoSDR)

add_executable(jimoSDR
    src/jimoSDR.cpp
    src/MainForm.cpp
    src/properties_panel.cpp
    src/user_draw_buttons.cpp
    src/device_properties.cpp
    src/sampling_mode.cpp
    src/DigitIncrementer.cpp
    src/number_display.cpp
    src/RadioReceiver.cpp
    src/SourcePanel.cpp
    src/GuiNotifier.cpp
    include/ControlSizes.h
    include/MainForm.h
    include/properties_panel.h
    include/user_draw_buttons.h
    include/device_properties.h
    include/exceptions.h
    include/sampling_mode.h
    include/DigitIncrementer.h
    include/number_display.h
    include/ReceiverAction.h
    include/ReceiverTask.h
    include/RadioReceiver.h
    include/SourcePanel.h
    include/GotReceiversEventArgs.h
    include/GotDeviceDriverKeyEventArgs.h
    include/GotSampleRatesEventArgs.h
    include/GotCurrentSampleRateEventArgs.h
    include/GuiNotifier.h
    include/SetSampleRateEventArgs.h
    include/SetSampleRateData.h
    )

target_include_directories(jimoSDR
    PUBLIC 
    include
    ${SoapySDR_SOURCE_DIR}/include)

target_link_libraries(jimoSDR
    PRIVATE
    sdr
    SoapySDR
    xtd)

target_compile_features(jimoSDR PRIVATE cxx_std_20)