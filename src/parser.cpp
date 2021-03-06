#include <QString>

#include "parser.hpp"
#include "tools.hpp"

mu::Parser Parser::sParser;

std::vector<double> Parser::sVariables;
std::vector<double> Parser::sPosition;
std::vector<double> Parser::sDirection;

void Parser::configureParser(const std::wstring& expression,
                             unsigned variablesCount)
{
    sParser.SetExpr(expression);

    sVariables = std::vector<double>(variablesCount);
    sPosition = std::vector<double>(variablesCount);
    sDirection = std::vector<double>(variablesCount);

    sParser.ClearVar();
    for (unsigned idx = 0; idx < variablesCount; ++idx)
        sParser.DefineVar((QString("x%1").arg(idx)).toStdWString(),
                          &sVariables[idx]);
}

double Parser::evaluateFunctionMono(const double alpha)
{
    Tools::convert_dimensions(alpha, sPosition, sDirection, sVariables);

    return sParser.Eval();
}

double Parser::evaluateFunctionMulti(const std::vector<double>& x)
{
    // TODO: Check if vectors assignment broke previosly set addresses.
    for (unsigned idx = 0; idx < x.size(); ++idx)
        sVariables[idx] = x[idx];

    return sParser.Eval();
}
