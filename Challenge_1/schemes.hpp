#ifndef SCHEMES_HPP
#define SCHEMES_HPP

#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

#include "learning_rate.hpp"
#include "params.hpp"

// Gradient descent
template <LearnRaterule choice>
std::vector<double> grad_descent(const Parameters &params) {
  std::vector<double> x_k = params.x_0;
  double alpha_0 = params.alpha_0;
  double mu = params.mu;
  double sigma = params.sigma;
  double eps_r = params.eps_r;
  double eps_s = params.eps_s;
  int max_iter = params.max_iter;

  bool max_iter_check = true;

  for (int k = 0; k < max_iter; ++k) {
    std::vector<double> grad_x_k = params.grad(x_k);
    double alpha_k = compute_alpha<choice>(params.fun, params.grad, x_k,
                                           alpha_0, mu, sigma, k);
    std::vector<double> x_k_1 = x_k - grad_x_k * alpha_k;

    double f_x_k = params.fun(x_k);
    double f_x_k_1 = params.fun(x_k_1);

    // step lenght check
    if (vector_norm(x_k_1 - x_k) < eps_s) {
      std::cout << "Verified step lenght check\n" << std::endl;
      max_iter_check = false;
      break;
    }

    // residual check
    if (std::abs(f_x_k_1 - f_x_k) < eps_r) {
      std::cout << "Verified residual check\n" << std::endl;
      max_iter_check = false;
      break;
    }

    x_k = x_k_1;
  }
  if (max_iter_check) {
    std::cout << "Reached max number of iterations. No convergence\n"
              << std::endl;
  }

  return x_k;
}

#endif // SCHEMES_HPP