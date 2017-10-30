#include <cmath>

#include "methods.hpp"

void sven_value(double (* f)(const double), const double initial,
    double& left_bound, double& right_bound)
{
    double step;
    double prev, curr, next;

    step = 0.01;

    if (init != 0.0)
        step *= fabs(init);

    if (f(init + step) > f(init))
        step = -step;

    curr = init;
    next = init + step;

    while (f(curr) > f(next))
    {
        step *= 2.0;

        prev = curr;
        curr = next;
        next += step;
    }

    if (curr < next)
    {
        left_bound = prev;
        right_bound = next;
    }
    else
    {
        left_bound = next;
        right_bound = prev;
    }
}
