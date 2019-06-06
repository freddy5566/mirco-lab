cmake_minimum_required(VERSION 2.8)

project(lab9)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(OpenCV REQUIRED)

# Populate a CMake variable with the sources
set(lab9
    mainwindow.ui
    mainwindow.cpp
    main.cpp
)
# Tell CMake to create the helloworld executable
add_executable(lab9 WIN32 ${lab9})
# Use the Widgets module from Qt 5
target_link_libraries(lab9 Qt5::Widgets)
target_link_libraries(lab9 ${OpenCV_LIBS} )