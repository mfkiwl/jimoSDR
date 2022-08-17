cmake_minimum_required(VERSION 3.22)

project(jimoSDR
    VERSION 0.1
    DESCRIPTION "A software defined radio receiver"
    LANGUAGES CXX)

if(MSVC)
    add_compile_options(/W3 /WX)
else()
    add_compile_options(-W -Wall -Werror)
endif()

add_subdirectory(src)