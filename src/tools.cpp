#include <cmath>
#include <vector>

#include "tools.hpp"

/*
 * Returns first partial derivative of function @f defined by @variableCount.
 * Checked: yes
 */
double Tools::first_derivative(double (*f)(const std::vector<double>&),
                               const std::vector<double>& x, int variableCount)
{
    static std::vector<double> auxiliaryOne = std::vector<double>(x);
    static std::vector<double> auxiliaryTwo = std::vector<double>(x);

    auxiliaryOne[variableCount] += EPSILON;
    auxiliaryTwo[variableCount] -= EPSILON;

    double result = (f(auxiliaryOne) - f(auxiliaryTwo)) / (2.0 * EPSILON);

    auxiliaryOne[variableCount] = x[variableCount];
    auxiliaryTwo[variableCount] = x[variableCount];

    return result;
}

/*
 * Returns gradient of function "f" of vector "x".
 * Checked: yes.
 */
std::vector<double> Tools::find_gradient(double (*f)(const std::vector<double>&),
    const std::vector<double>& x)
{
    std::vector<double> gradient;

    for (unsigned idx = 0; idx < x.size(); ++idx)
        gradient.push_back(first_derivative(f, x, idx));

    return std::move(gradient);
}


/*
 * Returns antigradient of function "f" of vector "x".
 * Checked: yes.
 */
std::vector<double> Tools::find_antigradient(double (*f)(const std::vector<double>&),
    const std::vector<double>& x)
{
    std::vector<double> auxiliary = find_gradient(f, std::move(x));

    for (auto value_itr = auxiliary.begin(); value_itr != auxiliary.end();
        ++value_itr)
        *value_itr = -(*value_itr);

    return std::move(auxiliary);
}

/*
 * Returns norm of vector "x".
 * Checked: yes.
 */
double Tools::find_norm(const std::vector<double>& x)
{
    double result = 0.0;

    for (auto value_itr = x.cbegin(); value_itr != x.cend(); ++value_itr)
        result += pow(*value_itr, 2.0);

    return sqrt(result);
}

void Tools::convert_dimensions(const double alpha,
    const std::vector<double>& initial, const std::vector<double>& direction,
    std::vector<double>& dst)
{
    for (unsigned idx = 0; idx < initial.size(); ++idx)
        dst[idx] = initial[idx] + alpha * direction[idx];
}
