#ifndef FUNCTIONS
#define FUNCTIONS

#define EPSILON 1E-6

std::vector<double> find_gradient(double (* f)(const std::vector<double>&),
    const std::vector<double>& x);
std::vector<double> find_antigradient(double (* f)(const std::vector<double>&),
    const std::vector<double>& x);
double find_norm(const std::vector<double>& x);

void convert_dimensions(const double alpha,
    const std::vector<double>& initial, const std::vector<double> direction,
    std::vector<double>& dst);

#endif
