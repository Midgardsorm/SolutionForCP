#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

namespace logger
{
    inline bool shouldLog = true;

    void log(std::string a_log);
} // namespace logger

#endif