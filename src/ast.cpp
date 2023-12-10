#include "ast.hpp"

#include <utility>

ast::Node::Node(int a_value) : value(a_value) {}

ast::Node::Node(const char a_op, std::unique_ptr<Node> &a_left, std::unique_ptr<Node> &a_right)
: op(a_op), left(std::move(a_left)), right(std::move(a_right))
{}
