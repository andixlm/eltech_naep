#include <cmath>

#include "methods.hpp"
#include "result.hpp"
#include "tools.hpp"

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
                          double& left_bound, double& right_bound,
                          const double epsilon)
{
    unsigned itr;
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
                        double& left_bound, double& right_bound,
                        const double epsilon)
{
    unsigned itr;
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
                                   double& left_bound, double& right_bound,
                                   const double epsilon)
{
    unsigned itr;
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
                                   double& left_bound, double& right_bound,
                                   const double epsilon)
{
    unsigned itr;
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
                              double& left_bound, double& right_bound,
                              const double epsilon)
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
                              double& left_bound, double& right_bound,
                              const double epsilon)
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
    unsigned itr;
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
                                     double& left_bound, double& right_bound,
                                     const double epsilon)
{
    unsigned itr;
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
                                    const double a,
                                    const double b,
                                    const double c)
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
                                    const double a,
                                    const double b,
                                    const double c)
{
    return (a + b) / 2.0 + (1.0 / 2.0) *
        (
            (f(a) - f(b)) * (b - c) * (c - a)
        ) /
        (
            f(a) * (b - c) + f(b) * (c - a) + f(c) * (a - b)
        );
}

static double get_approximation_four(double (*f)(const double),
                                     const double a,
                                     const double b,
                                     const double c)
{
    return b + (1.0 / 2.0) *
        (b - a) * (f(a) - f(c)) /
        (f(a) - 2.0 * f(b) + f(c));
}

double Methods::interpolation_extrapolation(double (*f)(const double),
                                            const double initial,
                                            const double epsilon)
{
    unsigned itr;
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
                       double& left_bound, double& right_bound,
                       const double epsilon)
{
    unsigned itr;
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
                    double& left_bound, double& cntr, double& right_bound,
                    const double epsilon)
{
    unsigned itr;
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

Result Methods::partan_two(double (*fMono)(const double alpha),
                           double (*fMulti)(const std::vector<double>& x),
                           std::vector<double>& variables,
                           std::vector<double>& initial,
                           std::vector<double>& direction,
                           const double epsilon)
{
    unsigned methodItrs = 0, accelerationItrs = 0;
    unsigned variablesCount = variables.size();

    double alpha, beta, leftBound, rightBound;

    std::vector<double> xOne = initial, xTwo(variablesCount),
            xThree(variablesCount), xFour(variablesCount),
            accelerationDirection(variablesCount);

    do
    {
        // Antigradient move from xOne to xTwo.
        initial = xOne;
        direction = Tools::find_antigradient(fMulti, initial);
        Methods::sven_value(fMono, INITIAL_ALPHA, leftBound, rightBound);
        alpha = Methods::fibonacci_two(fMono, leftBound, rightBound, epsilon);
        Tools::convert_dimensions(alpha, initial, direction, xTwo);
        ++methodItrs;

        for (unsigned count = 0; count < variablesCount; ++count)
        {
            // Antigradient move from xTwo to xThree.
            initial = xTwo;
            direction = Tools::find_antigradient(fMulti, initial);
            Methods::sven_value(fMono, INITIAL_ALPHA, leftBound, rightBound);
            alpha = Methods::fibonacci_two(fMono, leftBound, rightBound, epsilon);
            Tools::convert_dimensions(alpha, initial, direction, xThree);
            ++methodItrs;

            // Calculate acceleration direction as (xThree - xOne).
            for (unsigned idx = 0; idx < variablesCount; ++idx)
                accelerationDirection[idx] = xThree[idx] - xOne[idx];
            // Move along acceleration direction from xThree to xFour.
            initial = xThree;
            direction = accelerationDirection;
            Methods::sven_value(fMono, INITIAL_ALPHA, leftBound, rightBound);
            beta = Methods::fibonacci_two(fMono, leftBound, rightBound, epsilon);
            Tools::convert_dimensions(beta, initial, direction, xFour);
            ++accelerationItrs;

            xOne = xTwo;
            xTwo = xFour;
        }
    }
    while (Tools::find_norm(accelerationDirection) > epsilon &&
           methodItrs < MAX_ITERATIONS);

    return Result(methodItrs, accelerationItrs, xFour);
}

Result Methods::step_adjusting_newton(double (*fMono)(const double),
                                      double (*fMulti)(const std::vector<double>&),
                                      std::vector<double>& variables,
                                      std::vector<double>& initial,
                                      std::vector<double>& direction,
                                      const double epsilon)
{
    double alpha;
    unsigned iterations = 0, variablesCount = variables.size();
    std::vector<double> xOne(initial), xTwo(variablesCount),
            xDelta(variablesCount);

    do
    {
        std::vector<double> antigradient =
                Tools::find_antigradient(fMulti, xOne);
        matrix hessian = Tools::find_hessian(fMulti, xOne);

        xDelta = hessian.inverse() * antigradient;
        Tools::normalize(xDelta);

        alpha = 1.0;
        initial = xOne;
        direction = xDelta;
        while (fMono(alpha) > fMulti(initial) + epsilon *
               pow(Tools::find_norm(Tools::find_gradient(fMulti, initial)), 2.0)
               * alpha)
            alpha /= NEWTON_BETA_FACTOR;

        Tools::convert_dimensions(alpha, initial, direction, xTwo);

        xOne = xTwo;
        ++iterations;
    }
    while (Tools::find_norm(Tools::find_gradient(fMulti, xTwo)) > epsilon &&
           iterations < MAX_ITERATIONS);

    return Result(iterations, xTwo);
}

static matrix find_pearson_two_matrix(const matrix& prevMatrix,
                                      const std::vector<double>& prevPoint,
                                      const std::vector<double>& currPoint,
                                      const std::vector<double>& prevAntigradient,
                                      const std::vector<double>& currGradient)
{
    std::vector<double> deltaX(currPoint);
    for (unsigned idx = 0; idx < deltaX.size(); ++idx)
        deltaX[idx] -= prevPoint[idx];
    matrix deltaXMatrix("", deltaX);

    std::vector<double> gamma(currGradient);
    for (unsigned idx = 0; idx < gamma.size(); ++idx)
        gamma[idx] += prevAntigradient[idx];
    const matrix gammaMatrix("", gamma);

    matrix s = prevMatrix * gammaMatrix;

    matrix numerator = (deltaXMatrix - s) * deltaXMatrix.transpose();
    double denominator = (deltaXMatrix.transpose() * gammaMatrix).m_data[0][0];

    return prevMatrix + numerator / denominator;
}

Result Methods::quasinewton_pearson_two(double (*fMono)(const double alpha),
                                        double (*fMulti)(const std::vector<double>&),
                                        std::vector<double>& variables,
                                        std::vector<double>& initial,
                                        std::vector<double>& direction,
                                        const double epsilon)
{
    double alpha, leftBound, rightBound;
    unsigned iterations = 1, variablesCount = variables.size();

    std::vector<double> prevPoint(variablesCount), currPoint(initial),
            nextPoint(variablesCount);
    std::vector<double> currDirection(variablesCount);
    std::vector<double> prevAntigradient(variablesCount),
            currGradient(variablesCount);

    matrix prevA("", variablesCount, variablesCount),
            currA("", variablesCount, variablesCount);

    do
    {
        currGradient = Tools::find_gradient(fMulti, currPoint);

        std::vector<double> currAntigradient(currGradient);
        for (unsigned idx = 0; idx < variablesCount; ++idx)
            currAntigradient[idx] = -currAntigradient[idx];

        if ((iterations * variablesCount + 1) % (iterations) == 0)
        {
            currA = matrix("", 1.0, variablesCount, variablesCount);
            currDirection = currAntigradient;
        }
        else
        {
            currA = find_pearson_two_matrix(prevA, prevPoint, nextPoint,
                                            prevAntigradient, currGradient);
            currDirection = currA * currAntigradient;
        }

        initial = currPoint;
        direction = currDirection;
        Methods::sven_value(fMono, INITIAL_ALPHA, leftBound, rightBound);
        alpha = fibonacci_two(fMono, leftBound, rightBound, epsilon);
        Tools::convert_dimensions(alpha, initial, direction, nextPoint);

        // Update variables.
        prevPoint = currPoint;
        currPoint = nextPoint;

        prevAntigradient = currAntigradient;

        prevA = currA;

        ++iterations;
    }
    while (Tools::find_norm(Tools::find_gradient(fMulti, nextPoint)) > epsilon &&
           iterations - 1 < MAX_ITERATIONS);

    return Result(iterations - 1, nextPoint);
}

static double find_daniel_coefficient(const std::vector<double>& prevDir,
                                      const std::vector<double>& prevAntigradient,
                                      const std::vector<double>& currGradient)
{
    unsigned variablesCount = prevDir.size();

    std::vector<double> gamma(variablesCount);
    for (unsigned idx = 0; idx < variablesCount; ++idx)
        gamma[idx] = currGradient[idx] + prevAntigradient[idx];

    double numerator = 0.0, denominator = 0.0;
    for (unsigned idx = 0; idx < variablesCount; ++idx)
    {
        numerator += currGradient[idx] * gamma[idx];
        denominator += prevDir[idx] * gamma[idx];
    }

    return numerator / denominator;
}

Result Methods::mсg_daniel(double (*fMono)(const double alpha),
                           double (*fMulti)(const std::vector<double>&),
                           std::vector<double>& variables,
                           std::vector<double>& initial,
                           std::vector<double>& direction,
                           const double epsilon)
{
    double alpha, leftBound, rightBound;
    unsigned iterations = 1, variablesCount = variables.size();

    std::vector<double> xOne(initial), xTwo(variablesCount);
    std::vector<double> prevDirection(variablesCount),
            currDirection(variablesCount);
    std::vector<double> prevAntigradient(variablesCount),
            currGradient(variablesCount);

    do
    {
        currGradient = Tools::find_gradient(fMulti, xOne);

        std::vector<double> currAntigradient(currGradient);
        for (unsigned idx = 0; idx < variablesCount; ++idx)
            currAntigradient[idx] = -currAntigradient[idx];

        // Build currDirection.
        if ((iterations * variablesCount + 1) % (iterations) == 0)
        {
            currDirection = currAntigradient;
        }
        else
        {
            // Daniel ratio.
            double beta = find_daniel_coefficient(prevDirection,
                                                  prevAntigradient,
                                                  currGradient);

            // Correct prevDirection.
            for (unsigned idx = 0; idx < variablesCount; ++idx)
                prevDirection[idx] *= beta;

            // Calculate currDirection.
            for (unsigned idx = 0; idx < variablesCount; ++idx)
                currDirection[idx] = currAntigradient[idx] + prevDirection[idx];
        }

        initial = xOne;
        direction = currDirection;
        Methods::sven_value(fMono, INITIAL_ALPHA, leftBound, rightBound);
        alpha = fibonacci_two(fMono, leftBound, rightBound, epsilon);
        Tools::convert_dimensions(alpha, initial, direction, xTwo);

        xOne = xTwo;
        prevDirection = currDirection;
        prevAntigradient = currAntigradient;

        ++iterations;
    }
    while (Tools::find_norm(Tools::find_gradient(fMulti, xTwo)) > epsilon &&
           iterations - 1 < MAX_ITERATIONS);

    return Result(iterations - 1, xTwo);
}

Result Methods::powell_two(double (*fMono)(const double alpha),
                           double (*fMulti)(const std::vector<double>&),
                           std::vector<double>& variables,
                           std::vector<double>& initial,
                           std::vector<double>& direction,
                           const double epsilon)
{
    int iterations = 0;

    double alpha, leftBound, rightBound;

    std::vector<double> currentPoint = initial, nextPoint(initial.size());

    std::vector<std::vector<double>> initials;
    std::vector<std::vector<double>> directions(direction.size() + 1);
    std::vector<double> tempDirection(direction.size());

    // Initialize with zeros.
    for (unsigned idxAlpha = 0; idxAlpha < directions.size(); ++idxAlpha)
    {
        directions[idxAlpha] = std::vector<double>(direction.size());

        for (unsigned idxBeta = 0; idxBeta < direction.size(); ++idxBeta)
            directions[idxAlpha][idxBeta] = 0.0;
    }

    // Set directions to axes.
    for (unsigned idx = 0; idx < directions.size() - 1; ++idx)
        directions[idx][idx] = 1.0;
    directions[directions.size() - 1] = directions[0];

    do
    {
        initials.clear();

        // Move along all directions.
        for (unsigned idx = 0; idx < directions.size(); ++idx)
        {
            // Save point.
            initials.push_back(currentPoint);

            // Move along direction.
            initial = currentPoint;
            direction = directions[idx];
            Methods::sven_value(fMono, INITIAL_ALPHA, leftBound, rightBound);
            alpha = Methods::fibonacci_two(fMono, leftBound, rightBound, epsilon);
            Tools::convert_dimensions(alpha, initial, direction, nextPoint);

            currentPoint = nextPoint;
        }
        initials.push_back(nextPoint);

        // Last and second.
        for (unsigned idx = 0; idx < tempDirection.size(); ++idx)
            tempDirection[idx] =
                    initials[initials.size() - 1][idx] -
                    initials[1][idx];

        initial = nextPoint;
        direction = tempDirection;
        Methods::sven_value(fMono, INITIAL_ALPHA, leftBound, rightBound);
        alpha = Methods::fibonacci_two(fMono, leftBound, rightBound, epsilon);
        Tools::convert_dimensions(alpha, initial, direction, nextPoint);

        if (Tools::find_norm(tempDirection) <= epsilon)
            break;
        else
        {
            for (int idx = directions.size() - 1; idx > 0; --idx)
                directions[idx - 1] = directions[idx];

            directions[0] = directions[directions.size() - 1] = tempDirection;
        }
    }
    while (iterations++ < MAX_ITERATIONS);

    return Result(iterations, nextPoint);
}
