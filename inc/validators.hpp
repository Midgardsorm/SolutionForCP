#ifndef VALIDATORS_HPP
#define VALIDATORS_HPP

#include <string>

namespace customChecks
{
    bool checkParenthesis(const std::string& a_expr);

    template<typename Func, typename... Args>
    bool checkContainsOnly(const std::string& a_expr, Func filter, Args... args);

    bool checkArithmeticExpr(const std::string& a_expr);
} // namespace customChecks

namespace validators
{
    class ArithmeticExprValidator
    {
      public:
        bool validate(std::string a_expr) const;
    };
} // namespace validators

#endif