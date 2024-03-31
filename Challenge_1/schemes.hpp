#ifndef SCHEMES_HPP
#define SCHEMES_HPP

#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

#include "learning_rate.hpp"
#include "params.hpp"
#include "vector_utilities.hpp"

enum class Scheme { GradDescent, HeavyBall, Nesterov };

// Gradient descent
std::vector<double> grad_descent(const Parameters &params, const double alpha_k,
                                 std::vector<double> x_k) {
                                  // @note better pass vectors by const&
  std::vector<double> grad_x_k = params.grad(x_k);
  std::vector<double> x_k_next = x_k - alpha_k * grad_x_k;
  return x_k_next;
}

// Heavy Ball
std::vector<double> heavy_ball(const Parameters &params, const double alpha_k,
                               std::vector<double> &x_k,
                               std::vector<double> &x_k_prev) {
                                //@note pass by const& the vectors. They are not changed
                                // by the function
  double nu = params.nu;
  std::vector<double> grad_x_k = params.grad(x_k);
  std::vector<double> x_k_next =
      x_k - alpha_k * grad_x_k + nu * (x_k - x_k_prev);
  return x_k_next;
}

// Nesterov
std::vector<double> nesterov(const Parameters &params, const double alpha_k,
                             std::vector<double> &x_k,
                             std::vector<double> &x_k_prev) {
                              //@note again pass by const& the vectors
  double nu = params.nu;
  std::vector<double> y = x_k + nu * (x_k - x_k_prev);
  std::vector<double> grad_y = params.grad(x_k);
  std::vector<double> x_k_next = y - alpha_k * grad_y;
  return x_k_next;
//@note in this cases it is better to return the result as
// return y - alpha_k * grad_y;
// you avoid the copy of the vector if RVO can be applied
// It applies in all the functions

}

//
template <Scheme Sc_choice, LearnRaterule LR_choice>
std::vector<double> apply_scheme(const Parameters &params) {
  std::vector<double> x_k = params.x_0;
  double alpha_0 = params.alpha_0;
  double mu = params.mu;
  double sigma = params.sigma;
  double eps_r = params.eps_r;
  double eps_s = params.eps_s;
  int max_iter = params.max_iter;

  std::vector<double> x_k_prev = x_k;

  // bool max_iter_check = true;

  for (int k = 0; k < max_iter; ++k) {
    std::vector<double> x_k_next;
    double alpha_k = compute_alpha<LR_choice>(params.fun, params.grad, x_k,
                                              alpha_0, mu, sigma, k);

    if constexpr (Sc_choice == Scheme::GradDescent) {
      x_k_next = grad_descent(params, alpha_k, x_k);
    } else if constexpr (Sc_choice == Scheme::HeavyBall) {
      x_k_next = heavy_ball(params, alpha_k, x_k, x_k_prev);
    } else if constexpr (Sc_choice == Scheme::Nesterov) {
      x_k_next = nesterov(params, alpha_k, x_k, x_k_prev);
    }

    double f_x_k = params.fun(x_k);
    double f_x_k_next = params.fun(x_k_next);

    // step lenght check
    if (vector_norm(x_k_next - x_k) < eps_s) {
      // std::cout << "Verified step lenght check\n" << std::endl;
      // max_iter_check = false;
      break;
    }

    // residual check
    if (std::abs(f_x_k_next - f_x_k) < eps_r) {
      // std::cout << "Verified residual check\n" << std::endl;
      // max_iter_check = false;
      break;
    }

    x_k_prev = x_k;
    x_k = x_k_next;
  }
  // if (max_iter_check) {
  //   std::cout << "Reached max number of iterations. No convergence\n"
  //             << std::endl;
  // }

  return x_k;
}

#endif // SCHEMES_HPP