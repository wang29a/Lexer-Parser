cmake_minimum_required(VERSION 3.12)

# 指定库的名称和源文件
add_library(Lexer STATIC
        KeywordTable.cpp
        Lexer.cpp
        Token.cpp
        WangLexer.cpp
        )

# 指定库的头文件目录
target_include_directories(Lexer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})