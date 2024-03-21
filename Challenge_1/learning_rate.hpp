#ifndef LEARNING_RATE_HPP
#define LEARNING_RATE_HPP

#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

#include "vector_utilities.hpp"

// Armijo rule
double armijo_rule(
    const std::function<double(const std::vector<double> &)> &fun,
    const std::function<std::vector<double>(const std::vector<double> &)> &grad,
    const std::vector<double> &x_k, double alpha_0, double mu, double sigma) {
  double alpha = alpha_0;

  while (fun(x_k) - fun(x_k - grad(x_k) * alpha) <
         sigma * alpha * vector_norm(grad(x_k)) *
             vector_norm(grad(x_k))) { // alpha * grad(x_k)
    alpha /= 2;
  }

  return alpha;
}

// // Exponential decay
// double exp_decay(const double alpha_0, const int iter, double mu = 0.2) {
//   return alpha_0 * exp(-mu * iter)
// }

// // Inverse decay
// double inv_decay(const double alpha_0, const int iter, double mu = 0.2) {
//   return alpha_0 / (1 + mu * iter)
// }

////

#endif // LEARNING_RATE_HPP