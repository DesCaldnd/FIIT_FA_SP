add_subdirectory(tests)

add_library(
        mp_os_lggr_srvr_lggr
        src/server_logger.cpp
        src/server_logger_builder.cpp)

find_package(httplib CONFIG REQUIRED)
target_link_libraries(mp_os_lggr_srvr_lggr PRIVATE httplib::httplib)

target_include_directories(
        mp_os_lggr_srvr_lggr
        PUBLIC
        ./include)

target_link_libraries(
        mp_os_lggr_srvr_lggr
        PUBLIC
        mp_os_cmmn)
target_link_libraries(
        mp_os_lggr_srvr_lggr
        PUBLIC
        mp_os_lggr_lggr)
target_link_libraries(
        mp_os_lggr_srvr_lggr
        PUBLIC
        nlohmann_json::nlohmann_json)