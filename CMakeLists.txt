cmake_minimum_required(VERSION 3.17)
project(MiniHell C)

set(CMAKE_C_STANDARD 99)

add_executable(MiniHell ./main.c libft/ft_putchar.c termcap/termcap.c termcap/key_function.c termcap/dop_func.c parser/parser.c parser/pre_parser.c libft/drop_space.c other_fun.c libft/overfree.c)

target_link_libraries(MiniHell /Users/dpatrica/CLionProjects/MiniHell/libft/libft.a)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ltermcap")