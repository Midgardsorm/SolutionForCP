#include "validators.hpp"

#include <cctype>
#include <iostream>
#include <stack>

#include "logger.hpp"

bool customChecks::checkParenthesis(const std::string& a_expr)
{
    std::stack<char> st;
    for (auto& c : a_expr)
    {
        if (st.empty())
        {
            if (c == '(')
            {
                st.push(c);
            }
            else if (c == ')')
            {
                logger::log( "ERROR: In \"" + a_expr + "\" Not matching parenthesis");
                return false;
            }
        }
        else if (st.top() == '(' && c == ')')
        {
            st.pop();
        }
        else if (c=='(')
        {
            st.push(c);
        }
    }
    if (st.empty())
    {
        return true;
    }
    logger::log( "ERROR: In \"" + a_expr + "\" Wrong parenthesis");
    return false;
}

template<typename Func, typename... Args>
bool customChecks::checkContainsOnly(const std::string& a_expr, Func filter, Args... args)
{
    for (auto& c : a_expr)
    {
        if (!(filter(c) || ((c == args) || ...)))
        {
            logger::log( "ERROR: In \"" + a_expr + "\" Wrong character:" + c);
            return false;
        }
    }
    return true;
}

bool customChecks::checkArithmeticExpr(const std::string& a_expr)
{
    if (!(a_expr[0] == '(' || std::isdigit(a_expr.front())))
    {
        logger::log( "ERROR: In \"" + a_expr + "\" Wrong character:" + a_expr[0] + " idx: 0");
        return false;
    }

    int maxIdx = a_expr.size() - 1;

    for (int i = 1; i < maxIdx; ++i)
    {
        if ((a_expr[i-1] == '(' && !(std::isdigit(a_expr[i]) || a_expr[i] == ')' || a_expr[i] == '('))
             || ((a_expr[i-1] == ')' || std::isdigit(a_expr[i-1])) && (std::isdigit(a_expr[i]) || a_expr[i] == '('))
             || ((a_expr[i-1] == '+' || a_expr[i-1] == '-' || a_expr[i-1] == '*' || a_expr[i-1] == '/')
                  && (!std::isdigit(a_expr[i]) && a_expr[i] != '(')))
        {
            logger::log( "ERROR: In \"" + a_expr + "\" Wrong character:" + a_expr[i] + " idx: " + std::to_string(i));
            return false;
        }
    }

    if (a_expr[maxIdx] != ')' && !std::isdigit(a_expr[maxIdx]))
    {
        logger::log( "ERROR: In \"" + a_expr + "\" Wrong character:" + a_expr[maxIdx] + " idx: " + std::to_string(maxIdx));
        return false;
    }

    return true;
}

bool validators::ArithmeticExprValidator::validate(std::string a_expr) const
{
    return customChecks::checkContainsOnly(a_expr, [](const char c){ return std::isdigit(c); }, '(', ')', '+', '-', '*', '/')
        && customChecks::checkParenthesis(a_expr)
        && customChecks::checkArithmeticExpr(a_expr);
};