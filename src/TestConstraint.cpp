#include <iostream>
#include "TestConstraint.hpp"

ccgo::TestConstraint::TestConstraint(const std::string& name, const double& a) :
  LagrangeConstraint(name),
  _a(a) {
}

ccgo::TestConstraint::~TestConstraint() {
}

double ccgo::TestConstraint::getA() const {
  return _a;
}

double ccgo::TestConstraint::h(const Eigen::VectorXd& x) const {
  auto it = getTargets().begin();
  long bi = (*it).second->getBeginIndex();
  return x(bi) - _a;
}

Eigen::VectorXd ccgo::TestConstraint::dh(const Eigen::VectorXd& x) const {
  auto it = getTargets().begin();
  long bi = (*it).second->getBeginIndex();
  Eigen::VectorXd result = Eigen::VectorXd::Zero(x.size());
  result(bi) = 1;
  return result;
}

Eigen::MatrixXd ccgo::TestConstraint::d2h(const Eigen::VectorXd& x) const {
  return Eigen::MatrixXd::Zero(x.size(), x.size());
}
