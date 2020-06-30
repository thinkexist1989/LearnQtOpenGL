#cmake 3.10之后OpenGL才有import target
cmake_minimum_required(VERSION 3.10)

project(LearnQtOpenGL LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Gui Widgets OpenGL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Boost COMPONENTS date_time REQUIRED)
find_package(Assimp REQUIRED)

set(CHAPTERS
    1.getting_started
    2.lighting
    3.model_loading
)

set(1.getting_started
        2.1.hello_triangle
        2.2.hello_triangle_indexed
        3.1.shaders_uniform
        3.2.shaders_interpolation
        3.4.widget_in_mainwindow
        4.1.texture
        5.1.transformations
        6.1.coordinate_systems
        6.1.coordinate_systems_multiple
        7.1.camera
        7.1.camera_keyboard
        7.1.camera_keyboard_mouse
)

set(2.lighting
        1.colors
        2.phone_lighting_model
        3.materials
        4.lighting_map
        5.lighting_caster
        6.lighting_caster_point
        7.lighting_caster_spot
        8.multiple_lights
)

set(3.model_loading
        1.model_loading
)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${ASSIMP_INCLUDE_DIRS})
link_directories(${ASSIMP_LIBRARY_DIRS})

add_library(stb_image "src/stb_image.cpp")
set(LIBS stb_image ${ASSIMP_LIBRARIES})

if(WIN32)
    set(LIBS ${LIBS} Qt5::Gui Qt5::Widgets Qt5::OpenGL OpenGL::GL Boost::date_time ) #注意，windows下import target只有OpenGL::GL
elseif(UNIX AND NOT APPLE)
    set(LIBS ${LIBS} Qt5::Gui Qt5::Widgets Qt5::OpenGL OpenGL::OpenGL Boost::date_time)
else()
    set(LIBS )
endif(WIN32)

foreach(CHAPTER ${CHAPTERS})
    foreach(DEMO ${${CHAPTER}})
        file(GLOB SOURCE
            "src/${CHAPTER}/${DEMO}/*.h"
            "src/${CHAPTER}/${DEMO}/*.cpp"
            "src/${CHAPTER}/${DEMO}/*.ui"
            "src/${CHAPTER}/${DEMO}/*.qrc"
            "resources/*.qrc"
        )
        set(NAME "${CHAPTER}_${DEMO}")
        add_executable(${NAME} ${SOURCE})
        target_include_directories(${NAME} PUBLIC "src/${CHAPTER}/${DEMO}/")
        target_link_libraries(${NAME} ${LIBS})
    endforeach(DEMO)
endforeach(CHAPTER)

#if(ANDROID)
#  add_library(LearnQtOpenGL SHARED
#    main.cpp
#    widget.cpp
#    widget.h
#    widget.ui
#    res.qrc
#  )
#else()
#  add_executable(LearnQtOpenGL
#    main.cpp
#    widget.cpp
#    widget.h
#    widget.ui
#    res.qrc
#  )
#endif()

#target_link_libraries(LearnQtOpenGL PRIVATE Qt5::Widgets Qt5::OpenGL)
