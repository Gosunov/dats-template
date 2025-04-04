cmake_minimum_required(VERSION 3.10)
project(DatsCity VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

include_directories(
    ${CMAKE_SOURCE_DIR}/third_party/spdlog/include
    ${CMAKE_SOURCE_DIR}/third_party/json/include
    ${CMAKE_SOURCE_DIR}/third_party/argparse/include
    ${CMAKE_SOURCE_DIR}/third_party/cpr/include
    ${CMAKE_SOURCE_DIR}/third_party/rewind/rewind_viewer/include
    ${CMAKE_SOURCE_DIR}/src
)

add_subdirectory(third_party/spdlog)
add_subdirectory(third_party/cpr)
add_subdirectory(third_party/rewind)

file(GLOB COMMON_SOURCES "src/common/*.cpp")
file(GLOB CLIENT_SOURCES "src/client/*.cpp")
file(GLOB REPLAYER_SOURCES "src/replayer/*.cpp")

# === Client Executable ===
add_executable(client ${COMMON_SOURCES} ${CLIENT_SOURCES})
target_link_libraries(client PRIVATE spdlog::spdlog)
target_link_libraries(client PRIVATE cpr::cpr)

# === Replayer Executable ===
add_executable(replayer ${COMMON_SOURCES} ${REPLAYER_SOURCES})
target_link_libraries(replayer PRIVATE spdlog::spdlog)
target_link_libraries(client PRIVATE cpr::cpr)
target_link_libraries(replayer PRIVATE rewind_viewer_client)
