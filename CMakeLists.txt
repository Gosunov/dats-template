cmake_minimum_required(VERSION 3.10)
project(MyProgram VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(SRC_DIR src)
file(GLOB SOURCES "${SRC_DIR}/*.cpp")

add_executable(main ${SOURCES})

include_directories(
    ${CMAKE_SOURCE_DIR}/third_party/spdlog/include
    ${CMAKE_SOURCE_DIR}/third_party/json/include
    ${CMAKE_SOURCE_DIR}/third_party/argparse/include
    ${CMAKE_SOURCE_DIR}/third_party/cpr/include
)

add_subdirectory(third_party/spdlog)
target_link_libraries(main PRIVATE spdlog::spdlog)

add_subdirectory(third_party/cpr)
target_link_libraries(main PRIVATE cpr::cpr)
