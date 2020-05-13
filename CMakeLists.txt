cmake_minimum_required(VERSION 3.14)
project(lem_in C)

set(CMAKE_C_STANDARD 11)

include_directories(.
        ./libft/includes
        ./ft_printf/includes
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
        srcs/suurballe.c
        srcs/neigs_work.c
        srcs/bellman_ford.c
        srcs/recalc_paths.c)

add_subdirectory(ft_printf libft)

target_link_libraries(lem_in
        ftprintf
        ft
        )

add_subdirectory(visu_hex_dir)
