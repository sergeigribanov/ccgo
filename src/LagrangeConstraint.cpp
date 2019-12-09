#include <utility>
#include "LagrangeConstraint.hpp"

ccgo::LagrangeConstraint::LagrangeConstraint(const std::string& name) :
  ccgo::Constraint(name),
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

void ccgo::LagrangeConstraint::setLambdaFinal(const Eigen::VectorXd& x) {
  _lambdaFinal = x(getLambdaIndex());
}
