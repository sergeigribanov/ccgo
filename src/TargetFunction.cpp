#include <iostream>
#include <utility>
#include "TargetFunction.hpp"

ccgo::TargetFunction::TargetFunction(const std::string& name, const long& n) :
  Function(name),
  _xInitial(Eigen::VectorXd::Zero(n)),
  _xFinal(Eigen::VectorXd::Zero(n)) {
}

ccgo::TargetFunction::~TargetFunction() {
}

long ccgo::TargetFunction::getBeginIndex() const {
  return _beginIndex;
}

long ccgo::TargetFunction::getN() const {
  return _xInitial.size();
}

long ccgo::TargetFunction::getEndIndex() const {
  return _beginIndex + _xInitial.size();
}

const Eigen::VectorXd& ccgo::TargetFunction::getInitialParameters() const {
  return _xInitial;
}

const Eigen::VectorXd& ccgo::TargetFunction::getFinalParameters() const {
  return _xFinal;
}

void ccgo::TargetFunction::setInitialParameters(const Eigen::VectorXd& x) {
  if (x.size() == _xInitial.size()) {
    _xInitial = x;
    _xFinal = x;
  } else {
    // TODO: exception
  }
}

void ccgo::TargetFunction::setBeginIndex(const long& index) {
  _beginIndex = index;
}

double ccgo::TargetFunction::getTargetValue() const {
  return f(_xFinal);
}

double ccgo::TargetFunction::getTargetValue(const Eigen::VectorXd& xfull) const {
  return f(xfull.segment(getBeginIndex(), getN()));
}

void ccgo::TargetFunction::setFinalParameters(const Eigen::VectorXd& xfull) {
  _xFinal = xfull.segment(getBeginIndex(), getN());
}

void ccgo::TargetFunction::setPeriod(long index, double left, double right) {
  if (right <= left) {
    // TO DO: exception
  }
  if (index < _xInitial.size() && index >= 0) {
    _periodical.push_back(std::make_pair(index, std::make_pair(left, right)));
  } else {
    // TO DO: exception
  }
}

void ccgo::TargetFunction::checkPeriodical(Eigen::VectorXd* x) const {
  long index;
  int nsteps;
  double period;
  for (const auto& el : _periodical) {
    index = _beginIndex + el.first;
    if ((*x)[index] >= el.second.second) {
      period = el.second.second - el.second.first;
      nsteps = ((*x)[index] - el.second.second) / period + 1;
      (*x)[index] -=  nsteps * period;
    } else if ((*x)[index] < el.second.first) {
      period = el.second.second - el.second.first;
      nsteps = (el.second.first - (*x)[index]) / period + 1;
      (*x)[index] +=  nsteps * period;
    }
  }
}

bool ccgo::TargetFunction::havePeriodical() const {
  return _periodical.size() > 0;
}
