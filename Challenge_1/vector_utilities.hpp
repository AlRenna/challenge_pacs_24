#ifndef VECTOR_UTILITIES_HPP
#define VECTOR_UTILITIES_HPP

#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

std::vector<double> operator*(const double scalar,
                              const std::vector<double> &vec) {
  std::vector<double> result;
  for (const auto &elem : vec) {
    result.push_back(scalar * elem);
  }
  return result;
}

std::vector<double> operator*(const std::vector<double> &vec,
                              const double scalar) {
  return scalar * vec;
}

std::vector<double> operator+(const std::vector<double> &v1,
                              const std::vector<double> &v2) {
  std::vector<double> result;
  // assume for simplicity that v1 and v2 have the same lenght (they are points
  // in 2D)
  for (int k = 0; k < 2; ++k) {
    result.push_back(v1[k] + v2[k]);
  }
  return result;
}

std::vector<double> operator-(const std::vector<double> &v1,
                              const std::vector<double> &v2) {
  return v1 + (-1 * v2);
}

double vector_norm(const std::vector<double> &vec) {
  double sum = 0.0;
  for (double val : vec) {
    sum += val * val;
  }
  return std::sqrt(sum);
}

#endif // VECTOR_UTILITIES_HPP