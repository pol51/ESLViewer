cmake_minimum_required(VERSION 2.8.11)
project(ESLViewer)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

file(GLOB_RECURSE SRCS src/*.cpp src/*.c src/*.h *.md)
include_directories(src src/libesl/include)

file(GLOB_RECURSE IMAGES res/*.svg)
set(IMAGES_QRC ${CMAKE_CURRENT_BINARY_DIR}/res.qrc)
file(WRITE ${IMAGES_QRC} "<RCC>\n    <qresource prefix=\"/\">\n")
foreach(IMAGE_FILE ${IMAGES})
  file(RELATIVE_PATH IMAGE_FILE_RELATIVE_PATH ${CMAKE_CURRENT_BINARY_DIR} ${IMAGE_FILE})
  file(RELATIVE_PATH IMAGE_FILE_SHORT_NAME ${CMAKE_SOURCE_DIR}/res ${IMAGE_FILE})
  file(APPEND ${IMAGES_QRC} "        <file alias=\"${IMAGE_FILE_SHORT_NAME}\">${IMAGE_FILE_RELATIVE_PATH}</file>\n")
endforeach()
file(APPEND ${IMAGES_QRC} "    </qresource>\n</RCC>")

qt5_add_resources(RCC ${IMAGES_QRC})

add_executable(${PROJECT_NAME} ${SRCS} ${IMAGES} ${RCC})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets pthread)
qt5_use_modules(${PROJECT_NAME} Widgets) # this should not be needed as we use cmake >= 2.8.11 but apparently it is on Linux Mint 16
