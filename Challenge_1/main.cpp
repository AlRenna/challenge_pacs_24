#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

struct Parameters {
  std::function<double(const std::vector<double> &)> fun;
  std::function<std::vector<double>(const std::vector<double> &)> grad;
  std::vector<double> x_0;
  double eps_r;
  double eps_s;
  double alpha_0;
  int max_iter;
  double mu;
  double sigma;
};

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

std::vector<double> operator-(const std::vector<double> &v1,
                              const std::vector<double> &v2) {
  std::vector<double> result;
  // assume for simplicity that v1 and v2 have the same lenght (they are points
  // in 2D)
  for (int k = 0; k < 2; ++k) {
    result.push_back(v1[k] - v2[k]);
  }
  return result;
}

double vector_norm(const std::vector<double> &vec) {
  double sum = 0.0;
  for (double val : vec) {
    sum += val * val;
  }
  return std::sqrt(sum);
}

// Strategies to find alpha_k:
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

// Gradient descent
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
    double alpha_k =
        armijo_rule(params.fun, params.grad, x_k, alpha_0, mu, sigma);
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

double f(const std::vector<double> &x) {
  return x[0] * x[1] + 4 * pow(x[0], 4) + pow(x[1], 2) + 3 * x[0];
}

std::vector<double> grad_f(const std::vector<double> &x) {
  return {x[1] + 16 * pow(x[0], 3) + 3, x[0] + 2 * x[1]};
}

int main() {
  // Define optimization parameters
  Parameters params;
  params.fun = f;
  params.grad = grad_f;
  params.x_0 = {0, 0};
  params.eps_r = 1e-6;
  params.eps_s = 1e-6;
  params.alpha_0 = 1.0;
  params.max_iter = 1000;
  params.mu = 0.2;
  params.sigma = 0.1;

  // Perform gradient descent with Armijo rule
  std::vector<double> result = grad_descent(params);
  std::cout << "Minimum point found: (" << result[0] << ", " << result[1] << ")"
            << std::endl;
  std::cout << "Minimum value found: " << params.fun(result) << std::endl;

  return 0;
}