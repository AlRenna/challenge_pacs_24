#include "params.hpp"
#include "GetPot"

Parameters::Parameters(const std::string &filename) {

  GetPot datafile("data.txt");

  // const std::string fun_str = datafile(
  //     "fun", "x[0] * x[1] + 4 * pow(x[0], 4) + pow(x[1], 2) + 3 * x[0]");
  // const std::string dfun_str =
  //     datafile("grad", "{x[1] + 16 * pow(x[0], 3) + 3, x[0] + 2 * x[1]}");

  // fun =
  //     datafile("fun", x[0] * x[1] + 4 * pow(x[0], 4) + pow(x[1], 2) + 3 *
  //     x[0]);
  // grad = datafile("grad", {x[1] + 16 * pow(x[0], 3) + 3, x[0] + 2 * x[1]});

  x_0.push_back(datafile("initial_point_x", 0.0));
  x_0.push_back(datafile("initial_point_y", 0.0));
  eps_r = datafile("eps_r", 1e-6);
  eps_s = datafile("eps_s", 1e-6);
  alpha_0 = datafile("alpha_0", 1.0);
  max_iter = datafile("max_iter", 1000);
  mu = datafile("mu", 0.2);
  sigma = datafile("sigma", 0.1);
}
