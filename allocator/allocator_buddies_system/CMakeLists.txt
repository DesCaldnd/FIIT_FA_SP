add_subdirectory(tests)

add_library(
        sys_prog_allctr_allctr_bdds_sstm
        src/allocator_buddies_system.cpp)

target_include_directories(
        sys_prog_allctr_allctr_bdds_sstm
        PUBLIC
        ./include)

target_link_libraries(
        sys_prog_allctr_allctr_bdds_sstm
        PUBLIC
        sys_prog_cmmn)
target_link_libraries(
        sys_prog_allctr_allctr_bdds_sstm
        PUBLIC
        sys_prog_allctr_allctr)