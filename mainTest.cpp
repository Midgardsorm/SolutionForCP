#include <string>
#include <vector>

#include "logger.hpp"
#include "test.hpp"

int main(int argc, char *argv[])
{
    // We do not want error from test cases that fail on purpose, so we turn off logging.
    logger::shouldLog = false;

    std::vector<testCase> testCases{{"(4 + 5 * (7 - 3)) - 2",   true,   22},
                                    {"4+5+7/2",                 true,   12},
                                    {"1 - 2 - 3",               true,   -4},
                                    {"1 - (2 - 3)",             true,    2},
                                    {"7",                       true,    7},
                                    {"7/0",                     false,   0},
                                    {"7/(2-2)",                 false,   0},
                                    {"10 + 1",                  false,   0},
                                    {"-10",                     false,   0},
                                    {"(4++ 5 * (7 - 3)) - 2",   false,   0},
                                    {"((4 + 5 * (7 - 3)) - 2",  false,   0},
                                    {"Kałabanga",               false,   0},
                                    {"(4+ 5 * (7 - 3))) - 2",   false,   0},
                                    {"(",                       false,   0},
                                    {")",                       false,   0},
                                    {"",                        false,   0}};


    TEST test;
    test.test(testCases);

    return 0;
}