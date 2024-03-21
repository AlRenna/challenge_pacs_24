#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

#include "gradient_descent.hpp"
#include "params.hpp"

double f(const std::vector<double> &x) {
  return x[0] * x[1] + 4 * pow(x[0], 4) + pow(x[1], 2) + 3 * x[0];
}

std::vector<double> grad_f(const std::vector<double> &x) {
  return {x[1] + 16 * pow(x[0], 3) + 3, x[0] + 2 * x[1]};
}

int main() {
  // Define optimization parameters
  Parameters params("data.txt");
  params.fun = f;
  params.grad = grad_f;
  params.x_0 = {0, 0};
  // params.eps_r = 1e-6;
  // params.eps_s = 1e-6;
  // params.alpha_0 = 1.0;
  // params.max_iter = 1000;
  // params.mu = 0.2;
  // params.sigma = 0.1;

  // Perform gradient descent with Armijo rule
  std::vector<double> result = grad_descent(params);
  std::cout << "Minimum point found: (" << result[0] << ", " << result[1] << ")"
            << std::endl;
  std::cout << "Minimum value found: " << params.fun(result) << std::endl;

  return 0;
}