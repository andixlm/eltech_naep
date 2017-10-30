#ifndef FUNCTIONS
#define FUNCTIONS

#define EPSILON 1E-6

std::vector<double> find_gradient(double (* f)(const std::vector<double>&),
    const std::vector<double>& x);

#endif
