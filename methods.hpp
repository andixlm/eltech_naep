#ifndef METHODS
#define METHODS

#define MAX_ITERATIONS 30

void sven_value(double (* f)(const double), const double initial,
    double& left_bound, double& right_bound);
void sven_derivative(double (* df)(const double), const double initial,
    double& left_bound, double& right_bound);
    
double dichotomy(double (* f)(const double),
    double& left_bound, double& right_bound, const double epsilon);

#endif
