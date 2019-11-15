cmake_minimum_required(VERSION 3.14)
project(lem_in C)

set(CMAKE_C_STANDARD 11)

include_directories(.
        ./libft
        )

add_executable(lem_in
        lemin.c
        read_input.c
        lem_list.c
        rooms_parse.c
        line_parse.c
        links_parse.c
        print.c
        check_all.c
        graph_create.c
        calc_total_len.c
        paths_work.c
        )

add_dependencies(lem_in libft_target)
find_library(FT ft ./libft)
target_link_libraries(lem_in PUBLIC ${FT})

add_custom_target(
        libft_target
        COMMAND make
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/libft
)
