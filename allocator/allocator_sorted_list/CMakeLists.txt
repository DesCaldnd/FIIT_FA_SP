add_subdirectory(tests)

add_library(
        sys_prog_allctr_allctr_srtd_lst
        src/allocator_sorted_list.cpp)

target_include_directories(
        sys_prog_allctr_allctr_srtd_lst
        PUBLIC
        ./include)

target_link_libraries(
        sys_prog_allctr_allctr_srtd_lst
        PUBLIC
        sys_prog_cmmn)
target_link_libraries(
        sys_prog_allctr_allctr_srtd_lst
        PUBLIC
        sys_prog_allctr_allctr)