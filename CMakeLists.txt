cmake_minimum_required(VERSION 2.8.11)
project(ESLViewer)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

file(GLOB_RECURSE SRCS src/*.cpp src/*.c src/*.h *.md)
include_directories(src src/libesl/include)

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets pthread)
