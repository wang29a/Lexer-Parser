cmake_minimum_required(VERSION 3.12)

# 指定库的名称和源文件
add_library(LL STATIC
        LL.cpp
        )
# 指定库的头文件目录
target_include_directories(LL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})