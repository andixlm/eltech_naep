#include <cmath>

#include "methods.hpp"

void Methods::sven_value(double (*f)(const double), const double initial,
    double& left_bound, double& right_bound)
{
    double step;
    double prev, curr, next;

    step = 0.01;

    if (initial != 0.0)
        step *= fabs(initial);

    if (f(initial + step) > f(initial))
        step = -step;

    prev = curr = initial;
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

void Methods::sven_derivative(double (*df)(const double), const double initial,
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

double Methods::dichotomy(double (*f)(const double),
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

double Methods::bolzano(double (*df)(const double),
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

double Methods::golden_section_one(double (*f)(const double),
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

double Methods::golden_section_two(double (*f)(const double),
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

double Methods::fibonacci_one(double (*f)(const double),
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

double Methods::fibonacci_two(double (*f)(const double),
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

double Methods::newton(double (*df)(const double), double (*ddf)(const double),
    const double initial, const double epsilon)
{
    int itr;
    double curr, prev;

    itr = 0;
    curr = initial;

    do
    {
        ++itr;

        prev = curr;
        curr = prev - df(prev) / ddf(prev);
    }
    while (fabs(curr - prev) > epsilon && df(curr) > epsilon &&
        itr < MAX_ITERATIONS);

    return curr;
}

double Methods::linear_interpolation(double (*df)(const double),
    double& left_bound, double& right_bound, const double epsilon)
{
    int itr;
    double curr;

    itr = 0;

    do
    {
        ++itr;

        curr = right_bound - df(right_bound) * (right_bound - left_bound) /
            (df(right_bound) - df(left_bound));

        if (df(curr) > 0.0)
            right_bound = curr;
        else
            left_bound = curr;
    }
    while (epsilon && df(curr) > epsilon && itr < MAX_ITERATIONS);

    return curr;
}

static double get_approximation_one(double (*f)(const double),
    const double a, const double b, const double c)
{
    return (1.0 / 2.0) *
        (
            f(a) * (pow(b, 2.0) - pow(c, 2.0)) +
            f(b) * (pow(c, 2.0) - pow(a, 2.0)) +
            f(c) * (pow(a, 2.0) - pow(b, 2.0))
        ) /
        (
            f(a) * (b - c) +
            f(b) * (c - a) +
            f(c) * (a - b)
        );
}

static double get_approximation_two(double (*f)(const double),
    const double a, const double b, const double c)
{
    return (a + b) / 2.0 + (1.0 / 2.0) *
        (
            (f(a) - f(b)) * (b - c) * (c - a)
        ) /
        (
            f(a) * (b - c) + f(b) * (c - a) + f(c) * (a - b)
        );
}

static double get_approximation_three(double (*f)(const double),
    const double a, const double b, const double c)
{
    return b + (1.0 / 2.0) *
        (
            pow(b - a, 2.0) * (f(b) - f(c)) -
            pow(b - c, 2.0) * (f(b) - f(a))
        ) /
        (
            (b - a) * (f(b) - f(c)) -
            (b - c) * (f(b) - f(a))
        );
}

static double get_approximation_four(double (*f)(const double),
    const double a, const double b, const double c)
{
    return b + (1.0 / 2.0) *
        (b - a) * (f(a) - f(c)) /
        (f(a) - 2.0 * f(b) + f(c));
}

double Methods::interpolation_extrapolation(double (*f)(const double),
    const double initial, const double epsilon)
{
    int itr;
    double aprx, step;
    double left, center, right;

    step = 0.001;

    itr = 0;
    center = initial;

    do
    {
        ++itr;

        left = center - step;
        right = center + step;
        aprx = get_approximation_one(f, left, center, right);

        if (fabs((aprx - center) / center) < epsilon &&
            fabs((f(aprx) - f(center)) / f(center)) < epsilon)
            break;
        else
            center = aprx;
    }
    while (itr < MAX_ITERATIONS);

    return (center + aprx) / 2.0;
}

double Methods::powell(double (*f)(const double),
    double& left_bound, double& right_bound, const double epsilon)
{
    int itr;
    double cntr, aprx;

    itr = 0;
    cntr = (left_bound + right_bound) / 2.0;

    do
    {
        ++itr;

        aprx = (itr == 1) ?
            get_approximation_one(f, left_bound, cntr, right_bound) :
            get_approximation_two(f, left_bound, cntr, right_bound);

        if (fabs((cntr - aprx) / cntr) < epsilon &&
            fabs((f(cntr) - f(aprx)) / f(cntr)) < epsilon)
            return (cntr + aprx) / 2.0;

        if (f(cntr) < f(aprx))
        {
            if (cntr < aprx)
                right_bound = aprx;
            else
                left_bound = aprx;
        }
        else
        {
            if (cntr < aprx)
                left_bound = cntr;
            else
                right_bound = cntr;

            cntr = aprx;
        }
    }
    while (itr < MAX_ITERATIONS);

    return (cntr + aprx) / 2.0;
}

void Methods::sven_dsc(double (*f)(const double), const double initial,
    double& left_bound, double& cntr_ref, double& right_bound)
{
    double step;
    double prev, curr, next, cntr;

    step = 0.01;

    if (initial != 0.0)
        step *= fabs(initial);

    if (f(initial + step) > f(initial))
        step = -step;

    prev = curr = initial;
    next = initial + step;

    while (f(curr) > f(next))
    {
        step *= 2.0;

        prev = curr;
        curr = next;
        next += step;
    }

    cntr = (curr + next) / 2.0;

    if (f(cntr) < f(curr))
    {
        left_bound = curr;
        cntr_ref = cntr;
        right_bound = next;
    }
    else
    {
        left_bound = prev;
        cntr_ref = curr;
        right_bound = cntr;
    }
}

double Methods::dsc(double (*f)(double),
    double& left_bound, double& cntr, double& right_bound, const double epsilon)
{
    int itr;
    double aprx;

    itr = 0;

    do
    {
        ++itr;

        aprx = get_approximation_four(f, left_bound, cntr, right_bound);

        if (fabs((aprx - cntr) / cntr) < epsilon &&
            fabs((f(aprx) - f(cntr)) / f(cntr)) < epsilon)
            break;

        if (f(cntr) < f(aprx))
        {
            if (cntr < aprx)
                right_bound = aprx;
            else
                left_bound = aprx;
        }
        else
        {
            if (cntr < aprx)
                left_bound = cntr;
            else
                right_bound = cntr;

            cntr = aprx;
        }
    }
    while (itr < MAX_ITERATIONS);

    return (cntr + aprx) / 2.0;
}
