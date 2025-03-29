add_subdirectory(tests)

add_library(
        mp_os_lggr_clnt_lggr
        src/client_logger.cpp
        src/client_logger_builder.cpp)

target_include_directories(
        mp_os_lggr_clnt_lggr
        PUBLIC
        ./include)
target_link_libraries(
        mp_os_lggr_clnt_lggr
        PUBLIC
        mp_os_cmmn)
target_link_libraries(
        mp_os_lggr_clnt_lggr
        PUBLIC
        mp_os_lggr_lggr)
target_link_libraries(
        mp_os_lggr_clnt_lggr
        PUBLIC
        nlohmann_json::nlohmann_json)