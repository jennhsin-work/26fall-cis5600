cmake_minimum_required(VERSION 3.16)

project(hw01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hw01
    main.cpp
    vec4.h
    mat4.h
    vec4.cpp
    mat4.cpp
)

include(GNUInstallDirs)
install(TARGETS hw01
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
