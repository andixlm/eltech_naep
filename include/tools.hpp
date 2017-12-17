#ifndef FUNCTIONS
#define FUNCTIONS

#include "matrix.hpp"

namespace Tools
{
const double EPSILON = 1E-5;

double first_derivative(double (*f)(const std::vector<double>&),
                        const std::vector<double>& x, int variableCount);
double second_derivative(double (*f)(const std::vector<double>&),
                         const std::vector<double>& x,
                         int alphaVariableCount, int betaVariableCount);

std::vector<double> find_gradient(double (*f)(const std::vector<double>&),
    const std::vector<double>& x);
std::vector<double> find_antigradient(double (*f)(const std::vector<double>&),
    const std::vector<double>& x);
matrix find_hessian(double (*f)(const std::vector<double>&),
                    const std::vector<double>& x);
double find_norm(const std::vector<double>& x);

void normalize(std::vector<double>& x);
void convert_dimensions(const double alpha,
    const std::vector<double>& initial, const std::vector<double>& direction,
    std::vector<double>& dst);
}

#endif
