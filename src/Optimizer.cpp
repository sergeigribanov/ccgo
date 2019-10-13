#include <utility>
#include <iostream>
#include "NameException.hpp"
#include "Optimizer.hpp"

ccgo::Optimizer::Optimizer():
  _n(0), _nTotal(0) {
}

ccgo::Optimizer::~Optimizer() {
}

long ccgo::Optimizer::getN() const {
  return _n;
}

long ccgo::Optimizer::getNTotal() const {
  return _nTotal;
}

const Eigen::VectorXd&
ccgo::Optimizer::getInitialParameters(const std::string& name) const noexcept(false) {
  auto it = _targets.find(name);
  if (it == _targets.end()) {
    ccgo::NameException<ccgo::TargetFunction> e(name);
    std::cerr << e.what() << std::endl;
    throw(e);
  }
  return it->second->getInitialParameters();
}

const Eigen::VectorXd& ccgo::Optimizer::getFinalParameters(const std::string& name) const noexcept(false){
  auto it = _targets.find(name);
  if (it == _targets.end()) {
    ccgo::NameException<TargetFunction> e(name);
    std::cerr << e.what() << std::endl;
    throw(e);
  }
  return it->second->getFinalParameters();
}

void ccgo::Optimizer::addTarget(TargetFunction* obj) noexcept(false) {
  if (_targets.find(obj->getName()) == _targets.end()) {
    _targets.insert(std::make_pair(obj->getName(), obj));
    obj->setBeginIndex(_n);
    _n += obj->getN();
    _nTotal += obj->getN();
    incLambdaIndexes(obj->getN());
  } else {
    ccgo::NameException<TargetFunction> e(obj->getName());
    std::cerr << e.what() << std::endl;
    throw(e);
  }
}

void ccgo::Optimizer::addConstraint(Constraint* obj) noexcept(false) {
  if (_constraints.find(obj->getName()) == _constraints.end()) {
    _constraints.insert(std::make_pair(obj->getName(), obj));
    obj->setLambdaIndex(_nTotal);
    _nTotal += 1;
  } else {
    ccgo::NameException<ccgo::Constraint> e(obj->getName());
    std::cerr << e.what() << std::endl;
    throw(e);
  }
}

void ccgo::Optimizer::addTargetToConstraint(const std::string& targetFunctionName,
					    const std::string& constraintName) noexcept(false) {
  auto ci = _constraints.find(constraintName);
  auto ti = _targets.find(targetFunctionName);
  if (ti == _targets.end()) {
    ccgo::NameException<ccgo::TargetFunction> e(targetFunctionName);
    std::cerr << e.what() << std::endl;
    throw(e);
  }
  if (ci == _constraints.end()) {
    ccgo::NameException<ccgo::Constraint> e(constraintName);
    std::cerr << e.what() << std::endl;
    throw(e);
  }
  ci->second->add(ti->second);
}

void ccgo::Optimizer::setParameters(const std::string& name,
				    const Eigen::VectorXd& params) noexcept(false) {
  auto it = _targets.find(name);
  if (it == _targets.end()) {
    ccgo::NameException<ccgo::TargetFunction> e(name);
    std::cerr << e.what() << std::endl;
    throw(e);
  }
  it->second->setInitialParameters(params);
}

double ccgo::Optimizer::f(const Eigen::VectorXd& x) const {
  double result = 0;
  for (const auto& el : _targets) {
    if (el.second->isEnabled()) {
      result += el.second->f(x);
    }
  }
  for (const auto& el : _constraints) {
    if (el.second->isEnabled()) {
    result += el.second->f(x);
    }
  }
  return result;
}

Eigen::VectorXd ccgo::Optimizer::df(const Eigen::VectorXd& x) const {
  Eigen::VectorXd result(_nTotal);
  for (const auto& el : _targets) {
    if (el.second->isEnabled()) {
      result += el.second->df(x);
    }
  }
  for (const auto& el : _constraints) {
    if (el.second->isEnabled()) {
      result += el.second->df(x);
    }
  }
  return result;
}

Eigen::MatrixXd ccgo::Optimizer::d2f(const Eigen::VectorXd& x) const {
  Eigen::MatrixXd result(_nTotal, _nTotal);
  for (const auto& el : _targets) {
    if (el.second->isEnabled()) {
      result += el.second->d2f(x);
    }
  }
  for (const auto& el : _constraints) {
    if (el.second->isEnabled()) {
      result += el.second->d2f(x);
    }
  }
  return result;
}

void ccgo::Optimizer::enableConstraint(const std::string& name) noexcept(false) {
  auto it = _constraints.find(name);
  if (it != _constraints.end()) {
    if (!it->second->isEnabled()) {
      it->second->enable();
      it->second->setLambdaIndex(_nTotal);
      _nTotal += 1;
    }
  } else {
    ccgo::NameException<ccgo::Constraint> e(name);
    std::cerr << e.what() << std::endl;
    throw(e);
  }
}

void ccgo::Optimizer::disableConstraint(const std::string& name) noexcept(false) {
  auto it = _constraints.find(name);
  if (it != _constraints.end()) {
    if (it->second->isEnabled()) {
      it->second->disable();
      _nTotal -= 1;
      decLambdaIndexesByOne(it->second->getLambdaIndex());
    }
  } else {
    ccgo::NameException<ccgo::Constraint> e(name);
    std::cerr << e.what() << std::endl;
    throw(e);
  }
}

void ccgo::Optimizer::enableTarget(const std::string& name) noexcept(false) {
  auto it = _targets.find(name);
  if (it != _targets.end()) {
    if (!it->second->isEnabled()) {
      it->second->enable();
      it->second->setBeginIndex(_n);
      _n += it->second->getN();
      _nTotal += it->second->getN();
      incLambdaIndexes(it->second->getN());
    }
  } else {
    ccgo::NameException<ccgo::TargetFunction> e(name);
    std::cerr << e.what() << std::endl;
    throw(e);
  }
}

void ccgo::Optimizer::disableTarget(const std::string& name) noexcept(false) {
  auto it = _targets.find(name);
  if (it != _targets.end()) {
    if (it->second->isEnabled()) {
      it->second->disable();
      _n -= it->second->getN();
      _nTotal -= it->second->getN();
      decLambdaIndexes(it->second->getN());
    }
  } else {
    ccgo::NameException<ccgo::TargetFunction> e(name);
    std::cerr << e.what() << std::endl;
    throw(e);
  }
}

bool ccgo::Optimizer::optimize() {
  return false;
}

void ccgo::Optimizer::incLambdaIndexes(const long& n) {
  for (auto& el : _constraints) {
    if (el.second->isEnabled()) {
      el.second->setLambdaIndex(el.second->getLambdaIndex() + n);
    }
  }
}

void ccgo::Optimizer::decLambdaIndexes(const long& n) {
  for (auto& el : _constraints) {
    if (el.second->isEnabled()) {
      el.second->setLambdaIndex(el.second->getLambdaIndex() - n);
    }
  }
}

void ccgo::Optimizer::decLambdaIndexesByOne(const long& index) {
  for (auto& el : _constraints) {
    if (el.second->isEnabled() && el.second->getLambdaIndex() > index) {
      el.second->setLambdaIndex(el.second->getLambdaIndex() - 1);
    }
  }
}
