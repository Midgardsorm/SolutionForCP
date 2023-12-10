#include "evaluators.hpp"

#include <iostream>

#include "logger.hpp"

std::pair<int, bool> evaluators::custom::ArithmAstEvaluator::evaluate(std::unique_ptr<ast::Node> &a_root)
{
    if (a_root->left == nullptr)
    {
        return std::pair{a_root->value, true};
    }
    else
    {
        std::pair<int, bool> leftValue = evaluate(a_root->left);
        std::pair<int, bool> rightValue = evaluate(a_root->right);
        if (!leftValue.second || !rightValue.second)
        {
            return std::pair{0, false};
        }

        char op = a_root->op;
        if ((op == '/' && rightValue.first == 0))
        {
            logger::log("ERROR: Division by zero");
            return std::pair{0, false};
        }

        return std::pair{operations[op](leftValue.first, rightValue.first), true};
    }
}