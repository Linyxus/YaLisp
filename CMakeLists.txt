cmake_minimum_required(VERSION 3.17)
project(yalisp C)

set(CMAKE_C_STANDARD 99)

add_library(yalisp
        include/token.h
        src/token.c
        include/ctypes.h
        include/ast.h
        src/ast.c
        ulib_wrapper/readline.c
        ulib_wrapper/ulib.h
        include/eval.h
        src/eval.c
        include/lex.h src/lex.c
        include/total_map.h
        src/total_map.c)

target_include_directories(yalisp PUBLIC
        "ulib_wrapper"
        "src"
        "include"
)

add_executable(yl src/main.c)

target_link_libraries(yl yalisp)
