#include "s21_math.h"

int s21_isnan(double x) { return (x == x ? 0 : 1); }

int s21_isfinite(double x) { return (x <= DBL_MAX && x >= -DBL_MAX ? 0 : 1); }

long double s21_calculation(long double x, long double sum, long double prev,
                            long double fprev, long double term, long double i,
                            int count) {
  while (s21_fabs(term) >= s21_EPS) {
    i += 2.0;
    fprev *= (i * (i - 1));
    prev = prev * x * x;
    term = prev / fprev;
    sum += count * term;
    count = -count;
  }
  return sum;
}

int s21_abs(int x) { return x >= 0 ? x : -x; }

long double s21_acos(double x) {
  long double sum;
  if (s21_fabs(x) > 1) {
    sum = s21_NAN;
  } else if (x < 0) {
    sum = s21_PI - s21_asin(s21_sqrt(1 - x * x));
  } else {
    sum = s21_asin(s21_sqrt(1 - x * x));
  }
  return sum;
}

long double s21_asin(double x) {
  long double sum = x, prev = x, i = 1.0, del;
  if (s21_fabs(x) > 1) {
    sum = s21_NAN;
  } else if (s21_fabs(x) == 1) {
    sum = (x > 0 ? s21_PI / 2 : -s21_PI / 2);
  } else {
    while (s21_fabs(prev) >= s21_EPS) {
      prev = prev * x * x * i / (i + 1);
      del = (i + 2);

      sum += prev / del;
      i += 2.0;
    }
  }
  return sum;
}

long double s21_atan(double x) {
  long double sum;
  if (x == s21_POSINF) {
    sum = s21_PI / 2;
  } else if (x == s21_NEGINF) {
    sum = -s21_PI / 2;
  } else {
    sum = s21_asin(x / s21_sqrt(1 + x * x));
  }
  return sum;
}

long double s21_ceil(double x) {
  if (s21_isnan(x)) {
    return s21_NAN;
  } else {
    if (!s21_isfinite(x)) {
      if (x < LLONG_MAX && x > LLONG_MIN) {
        long long temp = x;
        if (x >= 0 && s21_fabs(x - temp) > s21_EPS) temp++;

        x = temp;
      }
    }
    return x;
  }
}

long double s21_cos(double x) {
  if (s21_isnan(x) || x == s21_POSINF || x == s21_NEGINF) {
    return s21_NAN;
  } else {
    x = s21_fmod(x, 2 * s21_PI);
    long double sum = 1, prev = 1, fprev = 1, term = x, i = 0.0;
    int count = -1;
    return s21_calculation(x, sum, prev, fprev, term, i, count);
  }
}

long double s21_exp(double x) {
  if (s21_isnan(x)) {
    return s21_NAN;
  } else {
    long double sum;
    if (x == s21_POSINF) {
      sum = s21_POSINF;
    } else if (x == s21_NEGINF) {
      sum = 0;
    } else {
      sum = 1;
      long double prev = 1;
      unsigned int i = 1;
      int flag = 1;
      if (x < 0) {
        x = -x;
        flag = 0;
      }
      while (s21_fabs(prev) > s21_EPS) {
        prev = prev * ((long double)x / i++);
        sum += prev;
        if (sum > DBL_MAX) break;
      }
      if (sum > DBL_MAX) {
        sum = (!flag ? 0 : s21_POSINF);
      } else if (!flag) {
        sum = 1 / sum;
      }
    }
    return sum;
  }
}

long double s21_fabs(double x) {
  if (s21_isnan(x)) {
    return s21_NAN;
  } else {
    return x >= 0.0 ? (long double)x : -(long double)x;
  }
}

long double s21_floor(double x) {
  if (s21_isnan(x)) {
    return s21_NAN;
  } else {
    if (!s21_isfinite(x)) {
      if (x < LLONG_MAX && x > LLONG_MIN) {
        long long temp = x;
        if (x < 0 && s21_fabs(x - temp) > s21_EPS) temp--;

        x = temp;
      }
    }
    return x;
  }
}

long double s21_fmod(double x, double y) {
  if (s21_isnan(x) || y == 0 || x == s21_POSINF || s21_isnan(y) ||
      x == s21_NEGINF) {
    return s21_NAN;
  } else {
    long double mod = 0;
    int flag = 0;
    if (x < 0) {
      x = -x;
      flag++;
    }
    if (y < 0) y = -y;
    if (x < y) {
      mod = (flag == 1 ? -x : x);
    } else if (x > y) {
      long long temp = (long double)x / (long double)y;
      mod = (long double)x - temp * (long double)y;
      mod = (!mod ? 0 : flag == 1 ? -mod : mod);
    }
    return mod;
  }
}

long double s21_log(double x) {
  double lg;
  if (x < 0.0 || s21_isnan(x)) {
    lg = s21_NAN;
  } else if (x == 0 || x == s21_POSINF) {
    lg = s21_POSINF;
  } else {
    int ex_pow = 0;
    lg = 0;
    double compare = 0;
    for (; x >= s21_E; x /= s21_E, ex_pow++) continue;
    for (int i = 0; i < 100; i++) {
      compare = lg;
      lg = compare + 2 * (x - s21_exp(compare)) / (x + s21_exp(compare));
    }
    lg += ex_pow;
  }
  return lg;
}

long double s21_sin(double x) {
  if (s21_isnan(x) || x == s21_POSINF || x == s21_NEGINF) {
    return s21_NAN;
  } else {
    x = s21_fmod(x, 2 * s21_PI);
    long double sum = x, prev = x, fprev = 1, i = 1.0, term = x;
    int count = -1;
    return s21_calculation(x, sum, prev, fprev, term, i, count);
  }
}

long double s21_sqrt(double x) {
  long double root;
  if (s21_isnan(x) || x < 0) {
    root = s21_NAN;
  } else {
    if (x == s21_POSINF) {
      root = s21_POSINF;
    } else {
      long double temp = 1;
      for (;;) {
        root = (temp + x / temp) / 2;
        if (s21_fabs(root - temp) < s21_EPS) break;
        temp = root;
      }
    }
  }
  return root;
}

long double s21_tan(double x) {
  if (s21_isnan(x)) {
    return s21_NAN;
  } else {
    long double res;
    x = s21_fmod(x, 2 * s21_PI);
    if (x == s21_PI / 2) {
      res = 16331239353195370L;
    } else if (x == -s21_PI / 2) {
      res = -16331239353195370L;
    } else {
      res = s21_sin(x) / s21_cos(x);
    }
    return res;
  }  //// не определен при углах 90 и 270 градусов (cos = 0)!!!
}
long double pow_for_int(double base, double exp) {
  long double total = 1;
  if (exp < 0) {
    exp *= -1;
    for (int i = 0; i < exp; i++) total *= base;
    total = 1 / total;
  } else if (exp > 0) {
    for (int i = 0; i < exp; i++) total *= base;
  }
  return total;
}

long double pow_for_frac(double base, double exp) {
  long double res;
  if (base == 0 && !s21_isnan(exp))
    res = exp < 0 ? s21_POSINF : 0;
  else if (base == -1 && (exp == s21_POSINF || exp == s21_NEGINF))
    res = 1;
  else if (base == 1)
    res = 1;
  else if (exp == 0)
    res = 1;
  else if (s21_isnan(base))
    res = s21_NAN;
  else if (exp == s21_POSINF)
    res = s21_fabs(base) < 1 ? 0 : s21_POSINF;
  else if (exp == s21_NEGINF)
    res = s21_fabs(base) < 1 ? s21_POSINF : 0;
  else if (base == s21_NEGINF && !s21_isnan(exp))
    res = exp < 0 ? 0 : s21_POSINF;
  else
    res = s21_exp(exp * s21_log(base));
  return res;
}

long double s21_pow(double base, double exp) {
  long double res = 0;
  long double condition = exp - (long long int)exp;
  if (condition <= 0.00000001 && condition >= -0.00000001 && !s21_isnan(exp) &&
      !s21_isnan(base)) {
    res = pow_for_int(base, exp);
  } else {
    res = pow_for_frac(base, exp);
  }

  return res;
}
/*int main() {
  // double base, x;
  // scanf("%lf%lf", &base, &x);
  // printf("%Lf\n%lf\n", s21_pow(base, x), pow(base, x));
  printf("%Lf\n%lf", s21_fmod(-9999999999999999, 2 * s21_PI),
         fmod(-9999999999999999, 2 * s21_PI));
}*/
