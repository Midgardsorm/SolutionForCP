#include "logger.hpp"

#include <iostream>

void logger::log(std::string a_log)
{
    if (shouldLog) {
        std::cout << a_log << "\n";
    }
}