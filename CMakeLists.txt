cmake_minimum_required(VERSION 3.12)
project(WangCompilers VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_COMPILE clang)
# set(CMAKE_CXX_COMPILE clang++)

add_subdirectory(src)
add_executable(WangCompilers main.cpp)

target_link_libraries(WangCompilers PRIVATE Lexer)
target_link_libraries(WangCompilers PRIVATE LL)
target_link_libraries(WangCompilers PRIVATE LR)

target_include_directories(WangCompilers PUBLIC
"${PROJECT_BINARY_DIR}"
"${PROJECT_SOURCE_DIR}/src"
"${PROJECT_SOURCE_DIR}/src/Lexer"
"${PROJECT_SOURCE_DIR}/src/LL"
"${PROJECT_SOURCE_DIR}/src/LR"
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
SET (CMAKE_CXX_FLAGS_INIT                "-Wall -std=c++20")
target_compile_options(WangCompilers PRIVATE -Wall -Wextra -Wpedantic -O2 -ggdb)

find_package(fmt REQUIRED)

target_link_libraries(WangCompilers PRIVATE fmt::fmt)