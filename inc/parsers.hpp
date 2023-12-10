#ifndef PARSERS_HPP
#define PARSERS_HPP

#include <memory>
#include <string>

#include "ast.hpp"
#include "logger.hpp"

namespace parsers
{
    namespace custom
    {
        class ArithmeticExprParser
        {
          public:
            bool parse(std::string a_expr, std::unique_ptr<ast::Node> &a_root) const;

          private:
            std::unique_ptr<ast::Node> parseNumber(const std::string& a_expr, size_t& a_idx) const;
            std::unique_ptr<ast::Node> parseFactor(const std::string& a_expr, size_t& a_idx) const;
            std::unique_ptr<ast::Node> parseTerm(const std::string& a_expr, size_t& a_idx) const;
            std::unique_ptr<ast::Node> parseExpression(const std::string& a_expr, size_t& a_idx) const;
        };

    } // namespace custom

    template <typename Validator, typename CustomParser>
    class Parser
    {
      public:
        Parser()
        : validator(std::make_unique<Validator>()), customParser(std::make_unique<CustomParser>())
        {}

        std::unique_ptr<ast::Node> parse(std::string a_expr) const
        {
            a_expr.erase(std::remove_if(a_expr.begin(), a_expr.end(), [](unsigned char c) { return std::isspace(c); }),
                            a_expr.end());

            if (!a_expr.size())
            {
                logger::log("ERROR: Empty expression.");
                return std::unique_ptr<ast::Node>(nullptr);
            }

            bool validated = validator->validate(a_expr);
            if (!validated)
            {
                return std::unique_ptr<ast::Node>(nullptr);
            }

            std::unique_ptr<ast::Node> root;
            bool parsed = customParser-> parse(a_expr, root);
            if (!parsed)
            {
                return std::unique_ptr<ast::Node>(nullptr);
            }

            return root;
        }

      private:
        std::unique_ptr<Validator> validator;
        std::unique_ptr<CustomParser> customParser;
    };

} // namespace parsers

#endif