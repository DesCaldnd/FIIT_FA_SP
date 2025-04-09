find_package(Crow CONFIG REQUIRED)

add_executable(
        mp_os_lggr_srvr_lggr_tests
        server_logger_tests.cpp)

target_link_libraries(
        mp_os_lggr_srvr_lggr_tests
        PRIVATE
        gtest_main
        Crow::Crow
)
target_link_libraries(
        mp_os_lggr_srvr_lggr_tests
        PRIVATE
        mp_os_lggr_srvr_lggr)

add_executable(
        serv_test
        server.cpp
        server.h
        server_test.cpp)

target_link_libraries(
        serv_test
        PRIVATE
        gtest_main
        Crow::Crow
)
target_link_libraries(
        serv_test
        PRIVATE
        mp_os_lggr_srvr_lggr)