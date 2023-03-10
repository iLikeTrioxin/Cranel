cmake_minimum_required(VERSION 3.5)

project(Cranel VERSION 0.1 LANGUAGES CXX)

add_subdirectory(deps)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(libfreenect REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Qt5Multimedia)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools Multimedia)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Multimedia)

set(TS_FILES Cranel_en_US.ts)

set(PROJECT_SOURCES
        Aliases.h
        CameraTracker.cpp
        CameraTracker.h
        CranelCamera.h
        PointFinder.cpp
        PointFinder.h
        TrackingDevice.h
        main.cpp
        KinectCamera.h
        KinectCamera.cpp
        OpencvCamera.cpp
        MultiCameraTracker.cpp
        TrackerClassifier.cpp
        MyBracelet.cpp
        i.hpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${TS_FILES})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Cranel
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Cranel APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(Cranel SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Cranel
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

message(STATUS ${libfreenect_INCLUDE_DIRS})
message(STATUS ${OpenCV_LIBS})
target_link_libraries(Cranel PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OpenCV_LIBS} freenectstatic)

set_target_properties(Cranel PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(Cranel PUBLIC ${OpenCV_INCLUDE_DIRS} ${libfreenect_INCLUDE_DIRS})

install(TARGETS Cranel
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Cranel)
endif()
