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

double bolzano(double (* df)(const double),
    double& left_bound, double& right_bound, const double epsilon)
{
    int itr;
    double pnt, drvt;

    itr = 0;
    do
    {
        ++itr;

        pnt = (left_bound + right_bound) / 2.0;
        drvt = df(pnt);

        if (drvt > 0.0)
            right_bound = pnt;
        else
            left_bound = pnt;
    }
    while ((drvt > epsilon || (right_bound - left_bound) > epsilon) &&
        itr < MAX_ITERATIONS);

    return (left_bound + right_bound) / 2.0;
}

double golden_section_one(double (* f)(const double),
    double& left_bound, double& right_bound, const double epsilon)
{
    int itr;
    double lambda, mu;

    itr = 0;
    lambda = left_bound +
        ((3.0 - sqrt(5.0)) / 2.0) * (right_bound - left_bound);
    mu = left_bound +
        ((sqrt(5.0) - 1.0) / 2.0) * (right_bound - left_bound);

    while (right_bound - left_bound > epsilon && itr < MAX_ITERATIONS)
    {
        ++itr;

        if (f(lambda) > f(mu))
        {
            left_bound = lambda;
            lambda = mu;
            mu = left_bound +
                ((sqrt(5.0) - 1.0) / 2.0) * (right_bound - left_bound);
        }
        else
        {
            right_bound = mu;
            mu = lambda;
            lambda = left_bound +
                ((3.0 - sqrt(5.0)) / 2.0) * (right_bound - left_bound);
        }
    }

    return (left_bound + right_bound) / 2.0;
}

double golden_section_two(double (* f)(const double),
    double& left_bound, double& right_bound, const double epsilon)
{
    int itr;
    double pnt, sym_pnt;

    itr = 0;
    pnt = left_bound +
        ((sqrt(5.0) - 1.0) / 2.0) * (right_bound - left_bound);

    do
    {
        ++itr;

        sym_pnt = left_bound + right_bound - pnt;

        if (pnt < sym_pnt)
            if (f(pnt) < f(sym_pnt))
                right_bound = sym_pnt;
            else
                left_bound = pnt, pnt = sym_pnt;
        else
            if (f(pnt) < f(sym_pnt))
                left_bound = sym_pnt;
            else
                right_bound = pnt, pnt = sym_pnt;
    }
    while (right_bound - left_bound > epsilon && itr < MAX_ITERATIONS);

    return (left_bound + right_bound) / 2.0;
}

static int get_iterations(const double rel, double& prev_ref, double& curr_ref)
{
    int itr;
    double befr_prev, prev, curr;

    itr = 2;
    befr_prev = 0.0; prev = 1.0; curr = 1.0;

    do
    {
        ++itr;

        befr_prev = prev;
        prev = curr;
        curr = prev + befr_prev;
    }
    while (curr <= rel);

    prev_ref = prev;
    curr_ref = curr;

    return itr;
}

double fibonacci_one(double (* f)(const double),
    double& left_bound, double& right_bound, const double epsilon)
{
    int itr, total_itrs;
    double delta;
    double lambda, mu;
    double curr, prev, befr_prev;

    itr = 0;
    total_itrs = get_iterations((right_bound - left_bound) / epsilon,
        prev, curr);

    delta = (right_bound - left_bound) / (curr + prev);

    befr_prev = curr - prev;
    lambda = left_bound + (befr_prev / curr) * (right_bound - left_bound);
    mu = left_bound + (prev / curr) * (right_bound - left_bound);

    while (itr < total_itrs - 1)
    {
        ++itr;

        if (f(lambda) < f(mu))
        {
            right_bound = mu;
            mu = lambda;
            lambda = left_bound +
                (befr_prev / curr) * (right_bound - left_bound);
        }
        else
        {
            left_bound = lambda;
            lambda = mu;
            mu = left_bound +
                (prev / curr) * (right_bound - left_bound);
        }

        curr = prev;
        prev = befr_prev;
        befr_prev = curr - prev;
    }

    mu = lambda + delta;
    if (f(lambda) < f(mu))
        return (left_bound + mu) / 2.0;
    else
        return (lambda + right_bound) / 2.0;
}

double fibonacci_two(double (* f)(const double),
    double& left_bound, double& right_bound, const double epsilon)
{
    int itr, total_itrs;
    double pnt, sym_pnt;
    double curr, prev;

    itr = 0;
    total_itrs = get_iterations((right_bound - left_bound) / epsilon,
        prev, curr);

    pnt = left_bound + (prev / curr) * (right_bound - left_bound) +
        (((total_itrs % 2 == 0) ? 1.0 : -1.0) / curr) * epsilon;

    do
    {
        ++itr;

        sym_pnt = left_bound + right_bound - pnt;

        if (pnt < sym_pnt)
            if (f(pnt) < f(sym_pnt))
                right_bound = sym_pnt;
            else
                left_bound = pnt, pnt = sym_pnt;
        else
            if (f(pnt) < f(sym_pnt))
                left_bound = sym_pnt;
            else
                right_bound = pnt, pnt = sym_pnt;
    }
    while (itr < total_itrs);

    return sym_pnt;
}
