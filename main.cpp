#include <iostream>
#include <memory>
#include <string>

#include "ast.hpp"
#include "evaluators.hpp"
#include "parsers.hpp"
#include "validators.hpp"

void printHelp(int a_argc);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printHelp(argc);
    }
    else
    {
        std::string expr(argv[1]);
        std::cout << "Parsing and evaluating expression: " << expr << "\n";

        parsers::Parser<validators::ArithmeticExprValidator, parsers::custom::ArithmeticExprParser> parser;
        evaluators::AstEvaluator<evaluators::custom::ArithmAstEvaluator> evaluator;
        std::unique_ptr<ast::Node> astRoot = parser.parse(expr);
        if (astRoot != nullptr)
        {
            auto [result, success] = evaluator.evaluate(astRoot);
            if (success)
            {
                std::cout << "Expression \"" << expr << "\" result: " << result << "\n";
            }
            else
            {
                std::cout << "Expression \"" << expr << "\" is invalid" << "\n";
            }
        }
        else
        {
            std::cout << "Expression \"" << expr << "\" is invalid" << "\n";
        }
    }

    return 0;
}

void printHelp(int a_argc) {
    std::cout << " --> Wrong number of arguments, have: " << a_argc -1 << ". But need onle 1.\n";
    std::cout << " --> Use double quotes for complex expressions.\n";
    std::cout << " --> For example: .\\ArithParsEval \"7 + 3 + 5 - (6 - 7)\"";
}