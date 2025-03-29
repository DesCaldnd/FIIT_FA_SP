#include <not_implemented.h>
// #include <httplib.h>
#include "../include/server_logger.h"

#ifdef _WIN32
#include <process.h>
#elif
#include <unistd.h>
#endif

server_logger::~server_logger() noexcept
{
    throw not_implemented("server_logger::~server_logger() noexcept", "your code should be here...");
}

logger& server_logger::log(
    const std::string &text,
    logger::severity severity) &
{
    throw not_implemented("const logger& server_logger::log(const std::string &, logger::severity) const &", "your code should be here...");
}

server_logger::server_logger(const std::string& dest,
                             const std::unordered_map<logger::severity, std::pair<std::string, bool>> &streams)
{
    throw not_implemented("server_logger::server_logger(const std::string& ,const std::unordered_map<logger::severity, std::pair<std::string, bool>> &)", "your code should be here...");
}

int server_logger::inner_getpid()
{
#ifdef _WIN32
    return ::_getpid();
#elif
    return getpid();
#endif
}

server_logger::server_logger(const server_logger &other)
{
    throw not_implemented("server_logger::server_logger(const server_logger &other)", "your code should be here...");
}

server_logger &server_logger::operator=(const server_logger &other)
{
    throw not_implemented("server_logger &server_logger::operator=(const server_logger &other)", "your code should be here...");
}

server_logger::server_logger(server_logger &&other) noexcept
{
    throw not_implemented("server_logger::server_logger(server_logger &&other) noexcept", "your code should be here...");
}

server_logger &server_logger::operator=(server_logger &&other) noexcept
{
    throw not_implemented("server_logger &server_logger::operator=(server_logger &&other) noexcept", "your code should be here...");
}
