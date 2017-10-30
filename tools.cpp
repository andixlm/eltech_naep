#include <vector>

#include "tools.hpp"

/*
 * Returns gradient of function "f" of vector "x".
 * Checked: yes.
 */
std::vector<double> find_gradient(double (* f)(const std::vector<double>&),
    const std::vector<double>& x)
{
    std::vector<double> gradient;
    std::vector<double> auxiliary = std::vector<double>(x);

    for (int idx = 0; idx < auxiliary.size(); ++idx)
    {
        auxiliary[idx] += EPSILON;
        gradient.push_back((f(auxiliary) - f(x)) / EPSILON);

        auxiliary[idx] = x[idx];
    }

    return std::move(gradient);
}
