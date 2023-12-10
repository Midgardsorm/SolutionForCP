#ifndef AST_HPP
#define AST_HPP

#include <memory>

namespace ast
{
    struct Node {
        Node() = default;

        Node(int a_value);

        Node(const char a_op, std::unique_ptr<Node> &a_left, std::unique_ptr<Node> &a_right);

        char op;
        int value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };
} // namespace ast

#endif