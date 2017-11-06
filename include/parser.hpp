#ifndef PARSER_HPP
#define PARSER_HPP

#include "muParser.h"

class Parser
{
public:
    static mu::Parser sParser;

    static std::vector<double> sVariables;
    static std::vector<double> sPosition;
    static std::vector<double> sDirection;

    static void configureParser(const std::wstring& expression,
                                unsigned variablesCount);

    static double evaluateFunctionMono(const double alpha);
    static double evaluateFunctionMulti(const std::vector<double>& x);
};

#endif // PARSER_HPP
