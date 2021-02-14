cmake_minimum_required(VERSION 3.15)
project(posapi)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -pthread -Wl,-rpath=/opt/posapi/lib -Wl,-rpath=./lib")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpermissive -pthread -Wl,-rpath=/opt/posapi/lib -Wl,-rpath=./lib")

add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Script Network HttpServer)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Script Qt5::Network Qt5::HttpServer crypto ssl sqlite3 PosAPI)

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(${PROJECT_NAME} main.cpp PosController.cpp PosController.h PosAPI.h ScheduleSender.cpp ScheduleSender.h Logger.cpp Logger.h)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
