#ifndef EVALUATORS_HPP
#define EVALUATORS_HPP

#include <functional>
#include <memory>
#include <unordered_map>
#include <utility>

#include "ast.hpp"

namespace evaluators
{
    namespace custom
    {
        class ArithmAstEvaluator
        {
          public:
            std::pair<int, bool> evaluate(std::unique_ptr<ast::Node> &a_root);

          private:
            std::unordered_map<char, std::function<int(int, int)>> operations = {
                    { '+' , [] (int a, int b) { return a + b; } },
                    { '-' , [] (int a, int b) { return a - b; } },
                    { '*' , [] (int a, int b) { return a * b; } },
                    { '/' , [] (int a, int b) { return a / b; } }
                };
        };

    } // namespace custom

    template <typename CustomAstEvaluator>
    class AstEvaluator
    {
      public:
        AstEvaluator()
        : evaluator(std::make_unique<CustomAstEvaluator>())
        {}

        std::pair<int, bool> evaluate(std::unique_ptr<ast::Node> &a_root) const
        {
           return evaluator->evaluate(a_root);
        }

      private:
        std::unique_ptr<CustomAstEvaluator> evaluator;
    };
} // namespace evaluators

#endif