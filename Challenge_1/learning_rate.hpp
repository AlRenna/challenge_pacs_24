#ifndef LEARNING_RATE_HPP
#define LEARNING_RATE_HPP

#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

#include "vector_utilities.hpp"

enum class LearnRaterule {
  ArmijoRule,
  ExponentialDecay,
  InverseDecay,
  ConstAlpha
};

// Armijo rule
double armijo_rule(
    const std::function<double(const std::vector<double> &)> &fun,
    const std::function<std::vector<double>(const std::vector<double> &)> &grad,
    const std::vector<double> &x_k, double alpha_0, double sigma) {
  double alpha = alpha_0;

  while (fun(x_k) - fun(x_k - alpha * grad(x_k)) <
         sigma * alpha * vector_norm(grad(x_k)) * vector_norm(grad(x_k))) {
    alpha /= 2;
  }

  return alpha;
}

// Exponential decay
double exp_decay(const double alpha_0, const int iter, double mu) {
  return alpha_0 * exp(-mu * iter);
}

// Inverse decay
double inv_decay(const double alpha_0, const int iter, double mu) {
  return alpha_0 / (1 + mu * iter);
}

//
template <LearnRaterule choice>
double compute_alpha(
    const std::function<double(const std::vector<double> &)> &fun,
    const std::function<std::vector<double>(const std::vector<double> &)> &grad,
    const std::vector<double> &x_k, double alpha_0, double mu, double sigma,
    int k) {

  int iter = k + 1;

  if constexpr (choice == LearnRaterule::ExponentialDecay) {
    return exp_decay(alpha_0, iter, mu);
  } else if constexpr (choice == LearnRaterule::InverseDecay) {
    return inv_decay(alpha_0, iter, mu);
  } else if constexpr (choice == LearnRaterule::ArmijoRule) {
    return armijo_rule(fun, grad, x_k, alpha_0, sigma);
  } else if constexpr (choice == LearnRaterule::ConstAlpha) {
    return alpha_0;
  }
}

#endif // LEARNING_RATE_HPP