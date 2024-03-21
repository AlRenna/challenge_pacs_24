#ifndef PARAMS_HPP
#define PARAMS_HPP

#include <functional>
#include <iostream>
#include <vector>

// #include "muparserX_fun.hpp"
// #include "muparser_fun.hpp"

struct Parameters {
  Parameters(const std::string &filename);

  std::function<double(const std::vector<double> &)> fun;
  // MuParerFun fun;
  std::function<std::vector<double>(const std::vector<double> &)> grad;
  // MuParserXFun<2> grad;

  std::vector<double> x_0;
  double eps_r;
  double eps_s;
  double alpha_0;
  int max_iter;
  double mu;
  double sigma;
};

#endif // PARAMS_HPP