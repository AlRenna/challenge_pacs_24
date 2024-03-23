#include "muparserx/mpParser.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

template <int N, class ArgumentType = std::vector<double>> class MuParserXFun {
public:
  MuParserXFun(const MuParserXFun &m) : m_parser(m.m_parser) {
    m_parser.DefineVar("x", &m_var);
  };

  MuParserXFun(const std::string &s) {
    try {
      m_parser.DefineVar("x", &m_var);
      m_parser.SetExpr(s);
    } catch (mu::ParserX::exception_type &e) {
      std::cerr << e.GetMsg() << std::endl;
    }
  };

  double operator()(const std::vector<double> &x) {
    m_var = x;
    double y = m_parser.Eval();
    return y;
  };

private:
  std::vector<double> m_var; // Define m_var as a vector for muParserX
  mu::ParserX m_parser;
};