cmake_minimum_required(VERSION 3.5)

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

find_package(Qt5 COMPONENTS Widgets OpenGL REQUIRED)
find_package(OpenGL REQUIRED)

set(CHAPTERS
    1.getting_started
)

set(1.getting_started
    2.1.hello_triangle
    2.2.hello_triangle_indexed
)

if(WIN32)
    set(LIBS Qt5::Widgets Qt5::OpenGL OpenGL::OpenGL)
elseif(UNIX AND NOT APPLE)
    set(LIBS Qt5::Widgets Qt5::OpenGL OpenGL::OpenGL)
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
        )
        set(NAME "${CHAPTER}_${DEMO}")
        add_executable(${NAME} ${SOURCE})
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
