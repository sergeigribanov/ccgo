#include <utility>
#include "Constraint.hpp"

ccgo::Constraint::Constraint(const std::string& name) :
  Function(name),
  _lambdaInitial(1),
  _lambdaFinal(1) {
}

ccgo::Constraint::~Constraint() {
}

long ccgo::Constraint::getLambdaIndex() const {
  return _lambdaIndex;
}

void ccgo::Constraint::setLambdaIndex(const long& index) {
  _lambdaIndex = index;
}

double ccgo::Constraint::getLambdaInitial() const {
  return _lambdaInitial;
}

double ccgo::Constraint::getLambdaFinal() const {
  return _lambdaFinal;
}

void ccgo::Constraint::setLambdaInitial(const double& lambda) {
  _lambdaInitial = lambda;
}

double ccgo::Constraint::f(const Eigen::VectorXd& x) const {
  return x(getLambdaIndex()) * h(x);
}

Eigen::VectorXd ccgo::Constraint::df(const Eigen::VectorXd& x) const {
  Eigen::VectorXd result(x.size());
  result = x(getLambdaIndex()) * dh(x);
  result(getLambdaIndex()) = h(x);
  return result; 
}

Eigen::MatrixXd ccgo::Constraint::d2f(const Eigen::VectorXd& x) const {
  Eigen::MatrixXd result(x.size(), x.size());
  const long li = getLambdaIndex();
  const long lip = li + 1;
  result = x(li) * d2h(x);
  result.block(0, li, x.size(), lip) = dh(x);
  result.block(li, 0, lip, x.size()) = result.block(0, li, x.size(), lip).transpose();
  result(li, li) = 0;
  return result;
}

void ccgo::Constraint::add(const TargetFunction* obj) {
  if (_targets.find(obj->getName()) == _targets.end()) {
    _targets.insert(std::make_pair(obj->getName(), obj));
  } else {
    // TODO: exception
  }
}
