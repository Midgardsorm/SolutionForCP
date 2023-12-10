#include "parsers.hpp"

#include <algorithm>
#include <iostream>
#include <utility>

bool parsers::custom::ArithmeticExprParser::parse(std::string a_expr, std::unique_ptr<ast::Node> &a_root) const
{
    size_t idx = 0;
    a_root = std::move(parseExpression(a_expr, idx));
    if (a_root)
    {
        return true;
    }
    else
    {
        return false;
    }
};

std::unique_ptr<ast::Node> parsers::custom::ArithmeticExprParser::parseNumber(const std::string& a_expr, size_t& a_idx) const
{
        const char c = a_expr[a_idx];
        auto node = std::make_unique<ast::Node>(c - '0');
        ++a_idx;
        return node;
}

std::unique_ptr<ast::Node> parsers::custom::ArithmeticExprParser::parseFactor(const std::string& a_expr, size_t& a_idx) const
{
    const char c = a_expr[a_idx];
    if (c == '(')
    {
        ++a_idx;
        std::unique_ptr<ast::Node> subExpression = parseExpression(a_expr, a_idx);

        // subExpression is ending on ')', so we increment index, to move to symbol after ')'.
        ++a_idx;
        return subExpression;
    }
    else
    {
        return parseNumber(a_expr, a_idx);
    }
}

std::unique_ptr<ast::Node> parsers::custom::ArithmeticExprParser::parseTerm(const std::string& a_expr, size_t& a_idx) const
{
    std::unique_ptr<ast::Node> leftNode = parseFactor(a_expr, a_idx);

    while (a_idx < a_expr.length() && (a_expr[a_idx] == '*' || a_expr[a_idx] == '/'))
    {
        char op = a_expr[a_idx];
        ++a_idx;
        std::unique_ptr<ast::Node> rightNode = parseFactor(a_expr, a_idx);

        auto node = std::make_unique<ast::Node>();
        node->op = op;
        node->left = std::move(leftNode);
        node->right = std::move(rightNode);

        leftNode = std::move(node);
    }

    return leftNode;
}

std::unique_ptr<ast::Node> parsers::custom::ArithmeticExprParser::parseExpression(const std::string& a_expr, size_t& a_idx) const
{
    std::unique_ptr<ast::Node> leftNode = parseTerm(a_expr, a_idx);

    while (a_idx < a_expr.length() && (a_expr[a_idx] == '+' || a_expr[a_idx] == '-'))
    {
        char op = a_expr[a_idx];
        ++a_idx;
        std::unique_ptr<ast::Node> rightNode = parseTerm(a_expr, a_idx);

        auto node = std::make_unique<ast::Node>();
        node->op = op;
        node->left = std::move(leftNode);
        node->right = std::move(rightNode);

        leftNode = std::move(node);
    }

    return leftNode;
}
