#include "TargetFunction.hpp"

ccgo::TargetFunction::TargetFunction(const std::string& name, const long& n) :
  Function(name),
  _xInitial(Eigen::VectorXd(n)),
  _xFinal(Eigen::VectorXd(n)) {
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
  } else {
    // TODO: exception
  }
}

void ccgo::TargetFunction::setBeginIndex(const long& index) {
  _beginIndex = index;
}

double ccgo::TargetFunction::f(const Eigen::VectorXd& x) const {
  return ownf(x.block(getBeginIndex(), 0, getEndIndex(), 1));
}

Eigen::VectorXd ccgo::TargetFunction::df(const Eigen::VectorXd& x) const {
  Eigen::VectorXd result(x.size());
  long eI = getEndIndex();
  result.block(getBeginIndex(), 0, eI, 1) =
    owndf(x.block(getBeginIndex(), 0, eI, 1));
  return result;
}

Eigen::MatrixXd ccgo::TargetFunction::d2f(const Eigen::VectorXd& x) const {
  Eigen::MatrixXd result(x.size(), x.size());
  long eI = getEndIndex();
  result.block(getBeginIndex(), getBeginIndex(), eI, eI) =
    ownd2f(x.block(getBeginIndex(), 0, eI, 1));
  return result;
}
