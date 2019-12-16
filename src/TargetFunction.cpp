#include "TargetFunction.hpp"

#include <iostream>
#include <utility>

ccgo::TargetFunction::TargetFunction(const std::string& name, const long& n)
    : Function(name), ParamContainer(n) {}

ccgo::TargetFunction::~TargetFunction() {}

double ccgo::TargetFunction::getTargetValue() const { return f(_xFinal); }

double ccgo::TargetFunction::getTargetValue(
    const Eigen::VectorXd& xfull) const {
  return f(xfull.segment(getBeginIndex(), getN()));
}
