cmake_minimum_required(VERSION 3.14)
project(lem_in C)

set(CMAKE_C_STANDARD 11)

include_directories(.
        ./libft
        ./libft/includes
        ./ft_printf/includes
        ./ft_printf
        ./includes
        )

add_executable(lem_in
        srcs/lemin.c
        srcs/read_input.c
        srcs/rooms_parse.c
        srcs/line_parse.c
        srcs/links_parse.c
        srcs/print.c
        srcs/check_all.c
        srcs/graph_create.c
        srcs/calc_total_len.c
        srcs/paths_work.c
        srcs/find_all_paths.c
        srcs/dijkstra_algo.c
        srcs/destroy.c
        srcs/ants_walk.c
        srcs/print_given_data.c
        srcs/matrix_links.c
        srcs/matrix.c
        srcs/suurballe.c
        )

add_dependencies(lem_in libftprintf_target libft_target)

find_library(FTPR ftprintf ./ft_printf)
find_library(FT ft ./libft)
target_link_libraries(lem_in PUBLIC ${FTPR} ${FT})

add_custom_target(
        libft_target
        COMMAND make
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/libft
)

add_custom_target(
        libftprintf_target
        COMMAND make
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/ft_printf
)
