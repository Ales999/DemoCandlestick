cmake_minimum_required(VERSION 2.8)

project(DemoCandlestick)

######## Complier message
set(CMAKE_BUILD_TYPE Release)
message(STATUS "System: ${CMAKE_SYSTEM}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler version: ${CMAKE_CXX_COMPILER_VERSION}")

######## Set C++ 11 standard
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
if (COMPILER_SUPPORTS_CXX11)
    if (CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif ()
else ()
    message(STATUS "Fatal Error: Your compiler doesn't support c++11, please install it!")
endif ()

######## Set output directories.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)

######## find all the source files.
file(GLOB HEADER_FILES include/*.h)
file(GLOB SOURCE_FILES src/*.cpp)

######## set for qt environment
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt/5.12.2/gcc_64)


find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Charts)


######## Set executable file name, and add the source files for it.
add_executable(DemoCandlestick ${HEADER_FILES} ${SOURCE_FILES})

######## link the depenceies
target_link_libraries(DemoCandlestick
        PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets Qt5::Charts)