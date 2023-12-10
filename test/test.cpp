#include "test.hpp"

#include <iostream>
#include <memory>

#include "ast.hpp"
#include "evaluators.hpp"
#include "parsers.hpp"
#include "validators.hpp"

void TEST::test(std::vector<testCase> &a_testCases)
{
    parsers::Parser<validators::ArithmeticExprValidator, parsers::custom::ArithmeticExprParser> parser;
    evaluators::AstEvaluator<evaluators::custom::ArithmAstEvaluator> evaluator;

    for (auto &[expr, shouldSucced, expectedResult]: a_testCases)
    {
        int result;
        std::unique_ptr<ast::Node> astRoot = parser.parse(expr);
        if (astRoot == nullptr)
        {
            std::cout << "Expression \"" << expr << "\" test: " << (shouldSucced == false ? "PASSED" : "FAILED") << "\n";
            continue;
        }
        else
        {
            auto [result, success] = evaluator.evaluate(astRoot);
            if (success)
            {
                if (!shouldSucced)
                {
                    std::cout << "Expression \"" << expr << "\" test: FAILED" << "\n";
                    continue;
                }
                std::cout << "Expression \"" << expr << "\" test: " << (expectedResult == result ? "PASSED" : "FAILED") << "\n";
            }
            else
            {
                std::cout << "Expression \"" << expr << "\" test: " << (shouldSucced == false ? "PASSED" : "FAILED") << "\n";
            }
        }
    }
}
