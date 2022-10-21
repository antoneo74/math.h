#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define s21_EPS 0.000000000001
#define s21_NAN 0.0 / 0.0
#define s21_POSINF 1.0 / 0.0
#define s21_NEGINF -1.0 / 0.0
#define s21_PI 3.141592653589793238462643383279502884197
#define s21_E 2.7182818284590452353602874713526624977572

int s21_isnan(double x);
int s21_isfinite(double x);
long double s21_calculation(long double x, long double sum, long double prev,
                            long double fprev, long double term, long double i,
                            int count);
int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double z);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);

#endif  // SRC_S21_MATH_H_
