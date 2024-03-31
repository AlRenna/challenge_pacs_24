#ifndef PARAMS_HPP
#define PARAMS_HPP

#include <functional>
#include <iostream>
#include <vector>

struct Parameters {
  Parameters(const std::string &filename);

  std::function<double(const std::vector<double> &)> fun;
  std::function<std::vector<double>(const std::vector<double> &)> grad;

  std::vector<double> x_0;
  //@note if you initiialize in-class you have automatically defaults
  // and then if you default the defualt constructor you can use the
  // (sorry about the multiplication of deaults...) you can use the class
  // without the need of a file. You gain in flexibility of use with little effort.
  double eps_r;
  double eps_s;
  double alpha_0;
  int max_iter;
  double mu;
  double nu;
  double sigma;
};

#endif // PARAMS_HPP