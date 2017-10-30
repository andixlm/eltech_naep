#ifndef METHODS
#define METHODS

void sven_value(double (* f)(const double), const double initial,
    double& left_bound, double& right_bound);
void sven_derivative(double (* df)(const double), const double initial,
    double& left_bound, double& right_bound);

#endif
