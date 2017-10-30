#ifndef METHODS
#define METHODS

#define MAX_ITERATIONS 30

void sven_value(double (* f)(const double), const double initial,
    double& left_bound, double& right_bound);
void sven_derivative(double (* df)(const double), const double initial,
    double& left_bound, double& right_bound);

double dichotomy(double (* f)(const double),
    double& left_bound, double& right_bound, const double epsilon);
double bolzano(double (* df)(const double),
    double& left_bound, double& right_bound, const double epsilon);

double golden_section_one(double (* f)(const double),
    double& left_bound, double& right_bound, const double epsilon);
double golden_section_two(double (* f)(const double),
    double& left_bound, double& right_bound, const double epsilon);

double fibonacci_one(double (* f)(const double),
    double& left_bound, double& right_bound, const double epsilon);
double fibonacci_two(double (* f)(const double),
    double& left_bound, double& right_bound, const double epsilon);

double newton(double (* df)(const double), double (* ddf)(const double),
    const double initial, const double epsilon);
double linear_interpolation(double (* df)(const double),
    double& left_bound, double& right_bound, const double epsilon);

double interpolation_extrapolation(double (* f)(const double),
    const double initial, const double epsilon);
double powell(double (* f)(const double),
    double& left_bound, double& right_bound, const double epsilon);

#endif
