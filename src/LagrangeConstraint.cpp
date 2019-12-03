#include <utility>
#include "LagrangeConstraint.hpp"

ccgo::LagrangeConstraint::LagrangeConstraint(const std::string& name) :
  Constraint(name),
  _lambdaInitial(2),
  _lambdaFinal(2) {
}

ccgo::LagrangeConstraint::~LagrangeConstraint() {
}

long ccgo::LagrangeConstraint::getLambdaIndex() const {
  return _lambdaIndex;
}

void ccgo::LagrangeConstraint::setLambdaIndex(const long& index) {
  _lambdaIndex = index;
}

double ccgo::LagrangeConstraint::getLambdaInitial() const {
  return _lambdaInitial;
}

double ccgo::LagrangeConstraint::getLambdaFinal() const {
  return _lambdaFinal;
}

void ccgo::LagrangeConstraint::setLambdaInitial(const double& lambda) {
  _lambdaInitial = lambda;
}

double ccgo::LagrangeConstraint::f(const Eigen::VectorXd& x) const {
  return x(getLambdaIndex()) * h(x);
}

Eigen::VectorXd ccgo::LagrangeConstraint::df(const Eigen::VectorXd& x) const {
  Eigen::VectorXd result = Eigen::VectorXd::Zero(x.size());
  result = x(getLambdaIndex()) * dh(x);
  result(getLambdaIndex()) = h(x);
  return result; 
}

Eigen::MatrixXd ccgo::LagrangeConstraint::d2f(const Eigen::VectorXd& x) const {
  Eigen::MatrixXd result = Eigen::MatrixXd::Zero(x.size(), x.size());
  const long li = getLambdaIndex();
  result = x(li) * d2h(x);
  result.block(0, li, x.size(), 1) = dh(x);
  result.block(li, 0, 1, x.size()) = result.block(0, li, x.size(), 1).transpose();
  result(li, li) = 0;
  return result;
}

void ccgo::LagrangeConstraint::setLambdaFinal(const Eigen::VectorXd& x) {
  _lambdaFinal = x(getLambdaIndex());
}
