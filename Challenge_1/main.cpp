#include <cmath>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <vector>

#include "params.hpp"
#include "schemes.hpp"

double f(const std::vector<double> &x) {
  return x[0] * x[1] + 4 * pow(x[0], 4) + pow(x[1], 2) + 3 * x[0];
}

std::vector<double> grad_f(const std::vector<double> &x) {
  return {x[1] + 16 * pow(x[0], 3) + 3, x[0] + 2 * x[1]};
}

void print_to_file(std::fstream &out_result, const std::string scheme,
                   const std::string rule, const std::vector<double> result,
                   Parameters &params) {
  out_result << scheme << " - " << rule << "\n"
             << "Minimum point found: (" << result[0] << ", " << result[1]
             << ")\n"
             << "Minimum value found: " << params.fun(result) << "\n\n";
}

int main() {
  // Define optimization parameters
  Parameters params("data.txt");
  params.fun = f;
  params.grad = grad_f;

  std::vector<double> result_AR =
      apply_scheme<Scheme::GradDescent, LearnRaterule::ArmijoRule>(params);

  std::vector<double> result_ED =
      apply_scheme<Scheme::HeavyBall, LearnRaterule::ConstAlpha>(params);

  std::vector<double> result_ID =
      apply_scheme<Scheme::Nesterov, LearnRaterule::ConstAlpha>(params);

  // OUTPUT TO TEXT FILE
  std::fstream out_result{"./results.txt", std::ios::out};
  if (!out_result) {
    std::cerr << " File open error " << std::endl;
    return 1; // exit the main
  } else {    // write to the output file
    std::cout << "Printing on file" << std::endl;

    print_to_file(out_result, "Gradient Descent", "Armijo Rule", result_AR,
                  params);
    print_to_file(out_result, "Heavy Ball", "Constant Alpha", result_ED,
                  params);
    print_to_file(out_result, "Nesterov", "Constant Alpha", result_ID, params);
  }
  out_result.close();

  std::cout << "File closed" << std::endl;

  return 0;
}