#ifndef METHODS
#define METHODS

#include "mainwindow.hpp"
#include "result.hpp"

namespace Methods
{
const double INITIAL_ALPHA = 0.01;
const unsigned MAX_ITERATIONS = 30;

void sven_value(double (*f)(const double), const double initial,
                double& left_bound, double& right_bound);
void sven_derivative(double (*df)(const double), const double initial,
                     double& left_bound, double& right_bound);

double dichotomy(double (*f)(const double),
                 double& left_bound, double& right_bound,
                 const double epsilon);
double bolzano(double (*df)(const double),
               double& left_bound, double& right_bound,
               const double epsilon);

double golden_section_one(double (*f)(const double),
                          double& left_bound, double& right_bound,
                          const double epsilon);
double golden_section_two(double (*f)(const double),
                          double& left_bound, double& right_bound,
                          const double epsilon);

double fibonacci_one(double (*f)(const double),
                     double& left_bound, double& right_bound,
                     const double epsilon);
double fibonacci_two(double (*f)(const double),
                     double& left_bound, double& right_bound,
                     const double epsilon);

double newton(double (*df)(const double), double (*ddf)(const double),
              const double initial, const double epsilon);
double linear_interpolation(double (*df)(const double),
                            double& left_bound, double& right_bound,
                            const double epsilon);

double interpolation_extrapolation(double (*f)(const double),
                                   const double initial, const double epsilon);
double powell(double (*f)(const double),
              double& left_bound, double& right_bound, const double epsilon);

void sven_dsc(double (*f)(const double), const double initital,
              double& left_bound, double& cntr_ref, double& right_bound);
double dsc(double (*f)(double),
           double& left_bound, double& cntr, double& right_bound,
           const double epsilon);

Result partan_two(double (*fMono)(const double alpha),
                  double (*fMulti)(const std::vector<double>&),
                  std::vector<double>& variables,
                  std::vector<double>& initial,
                  std::vector<double>& direction,
                  const double epsilon);
}

#endif
