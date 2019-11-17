cmake_minimum_required(VERSION 3.14)
project(lem_in C)

set(CMAKE_C_STANDARD 11)

include_directories(.
        ./libft
        ./libft/includes
        ./includes
        )

add_executable(lem_in
        srcs/lemin.c
        srcs/read_input.c
        srcs/lem_list.c
        srcs/rooms_parse.c
        srcs/line_parse.c
        srcs/links_parse.c
        srcs/print.c
        srcs/check_all.c
        srcs/graph_create.c
        srcs/calc_total_len.c
        srcs/paths_work.c
        srcs/mehmet_algo.c
        srcs/find_all_paths.c
        srcs/dijkstra_algo.c
        srcs/destroy.c
        )

add_dependencies(lem_in libft_target)
find_library(FT ft ./libft)
target_link_libraries(lem_in PUBLIC ${FT})

add_custom_target(
        libft_target
        COMMAND make
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/libft
)
