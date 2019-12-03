#include "ParamContainer.hpp"

ccgo::ParamContainer::ParamContainer(const long& n) :
  _xInitial(Eigen::VectorXd::Zero(n)),
  _xFinal(Eigen::VectorXd::Zero(n)) {
}

ccgo::ParamContainer::~ParamContainer() {
}

long ccgo::ParamContainer::getBeginIndex() const {
  return _beginIndex;
}

long ccgo::ParamContainer::getN() const {
  return _xInitial.size();
}

const Eigen::VectorXd& ccgo::ParamContainer::getInitialParameters() const {
  return _xInitial;
}

const Eigen::VectorXd& ccgo::ParamContainer::getFinalParameters() const {
  return _xFinal;
}

void ccgo::ParamContainer::setInitialParameters(const Eigen::VectorXd& x) {
  if (x.size() == _xInitial.size()) {
    _xInitial = x;
    _xFinal = x;
  } else {
    // TODO: exception
  }
}

void ccgo::ParamContainer::setBeginIndex(const long& index) {
  _beginIndex = index;
}

void ccgo::ParamContainer::setFinalParameters(const Eigen::VectorXd& xfull) {
  _xFinal = xfull.segment(getBeginIndex(), getN());
}

void ccgo::ParamContainer::setPeriod(long index, double left, double right) {
  if (right <= left) {
    // TO DO: exception
  }
  if (index < _xInitial.size() && index >= 0) {
    _periodical.push_back(std::make_pair(index, std::make_pair(left, right)));
  } else {
    // TO DO: exception
  }
}

void ccgo::ParamContainer::checkPeriodical(Eigen::VectorXd* x) const {
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

bool ccgo::ParamContainer::havePeriodical() const {
  return _periodical.size() > 0;
}
