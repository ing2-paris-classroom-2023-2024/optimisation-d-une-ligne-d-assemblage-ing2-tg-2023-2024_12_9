cmake_minimum_required(VERSION 3.23)
project(optimisation_d_une_ligne_d_assemblage_td12_grp9 C)

set(CMAKE_C_STANDARD 11)

add_executable(optimisation_d_une_ligne_d_assemblage_td12_grp9
        main.c
        exclusion.c
        exclusion.h
        precedence.c
        precedence.h
        temps_de_cycle.c
        temps_de_cycle.h
        structure.c
        structure.h)
