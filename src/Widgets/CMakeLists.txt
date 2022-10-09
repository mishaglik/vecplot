cmake_minimum_required(VERSION 3.10)

set (AGL_WIDGETS_SOURCES
    Button.cpp
    Widget.cpp
)

set (AGL_WIDGETS_HEADERS
    Button.hpp
    Widget.hpp
)


add_library(Widgets ${AGL_WIDGETS_SOURCES} ${AGL_WIDGETS_HEADERS})

target_link_libraries(Widgets PUBLIC AbstractGL)
target_link_libraries(Widgets PRIVATE MGeomerty LogUtils)

target_include_directories(Widgets PUBLIC "${PROJECT_SOURCE_DIR}/src")