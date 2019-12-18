#include "EqualityLagrangeConstraint.hpp"

#include <iostream>
#include <utility>

ccgo::EqualityLagrangeConstraint::EqualityLagrangeConstraint(
    const std::string& name)
    : ccgo::LagrangeConstraint(name) {}

ccgo::EqualityLagrangeConstraint::~EqualityLagrangeConstraint() {}

double ccgo::EqualityLagrangeConstraint::f(const Eigen::VectorXd& x) const {
  return x(getLambdaIndex()) * h(x);
}

Eigen::VectorXd ccgo::EqualityLagrangeConstraint::df(
    const Eigen::VectorXd& x) const {
  Eigen::VectorXd result = Eigen::VectorXd::Zero(x.size());
  result = x(getLambdaIndex()) * dh(x);
  result(getLambdaIndex()) = h(x);
  return result;
}

Eigen::MatrixXd ccgo::EqualityLagrangeConstraint::d2f(
    const Eigen::VectorXd& x) const {
  Eigen::MatrixXd result = Eigen::MatrixXd::Zero(x.size(), x.size());
  const long li = getLambdaIndex();
  result = x(li) * d2h(x);
  Eigen::VectorXd tmpDh = dh(x);
  result.block(0, li, x.size(), 1) = tmpDh;
  result.block(li, 0, 1, x.size()) = tmpDh.transpose();
  result(li, li) = 0;
  return result;
}
