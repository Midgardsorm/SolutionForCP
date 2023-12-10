#ifndef TEST_HPP
#define TEST_HPP

#include <string>
#include <vector>
#include <tuple>

using testCase = std::tuple<std::string, bool, int>;

class TEST
{
  public:
    void test(std::vector<testCase> &a_testCases);
};

#endif