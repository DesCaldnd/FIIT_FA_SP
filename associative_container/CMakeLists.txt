add_subdirectory(indexing_tree)

add_library(
        sys_prog_assctv_cntnr
        include/associative_container.h
        src/hhh.cpp)

target_include_directories(
        sys_prog_assctv_cntnr
        PUBLIC
        ./include)

target_link_libraries(
        sys_prog_assctv_cntnr
        PUBLIC
        sys_prog_cmmn)
target_link_libraries(
        sys_prog_assctv_cntnr
        PUBLIC
        sys_prog_allctr_allctr)