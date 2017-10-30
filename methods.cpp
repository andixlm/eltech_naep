#include <cmath>

#include "methods.hpp"

void sven_value(double (* f)(const double), const double initial,
    double& left_bound, double& right_bound)
{
    double step;
    double prev, curr, next;

    step = 0.01;

    if (initial != 0.0)
        step *= fabs(initial);

    if (f(initial + step) > f(initial))
        step = -step;

    curr = initial;
    next = initial + step;

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

void sven_derivative(double (* df)(const double), const double initial,
    double& left_bound, double& right_bound)
{
    double step;
    double prev, curr;

    step = 0.01;

    if (initial != 0.0)
        step *= fabs(initial);

    if (df(initial) > 0.0)
        step = -step;

    prev = initial;
    curr = initial + step;

    while (copysignf(1.0, df(prev)) * copysignf(1.0, df(curr)) > 0.0)
    {
        step *= 2.0;

        prev = curr;
        curr += step;
    }

    if (prev < curr)
    {
        left_bound = prev;
        right_bound = curr;
    }
    else
    {
        left_bound = curr;
        right_bound = prev;
    }
}

double dichotomy(double (* f)(const double),
    double& left_bound, double& right_bound, const double epsilon)
{
    int itr;
    double delta;
    double lambda, mu;

    itr = 0;
    delta = 0.1 * epsilon;

    do
    {
        ++itr;

        lambda = (left_bound + right_bound - delta) / 2.0;
        mu = (left_bound + right_bound + delta) / 2.0;

        if (f(lambda) < f(mu))
            right_bound = mu;
        else
            left_bound = lambda;
    }
    while (right_bound - left_bound > epsilon && itr < MAX_ITERATIONS);

    return (left_bound + right_bound) / 2.0;
}
