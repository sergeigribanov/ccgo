#include <utility>
#include "Optimizer.hpp"

ccgo::Optimizer::Optimizer() {
}

ccgo::Optimizer::~Optimizer() {
}

long ccgo::Optimizer::getN() const {
  return _n;
}

long ccgo::Optimizer::getNTotal() const {
  return _nTotal;
}

const Eigen::VectorXd& ccgo::Optimizer::getInitialParameters(const std::string& name) const {
  auto it = _targets.find(name);
  if (it == _targets.end()) {
    // TODO: exception
  }
  return it->second->getInitialParameters();
}

const Eigen::VectorXd& ccgo::Optimizer::getFinalParameters(const std::string& name) const {
  auto it = _targets.find(name);
  if (it == _targets.end()) {
    // TODO: exception
  }
  return it->second->getFinalParameters();
}

void ccgo::Optimizer::addTarget(TargetFunction* obj) {
  if (_targets.find(obj->getName()) == _targets.end()) {
    _targets.insert(std::make_pair(obj->getName(), obj));
  } else {
    // TODO: exception
  }
}

void ccgo::Optimizer::addConstraint(Constraint* obj) {
  if (_constraints.find(obj->getName()) == _constraints.end()) {
    _constraints.insert(std::make_pair(obj->getName(), obj));
  } else {
    // TODO: exception
  }
}

void ccgo::Optimizer::addTargetToConstraint(const std::string& targetFunctionName,
			  const std::string& constraintName) {
  auto ci = _constraints.find(constraintName);
  auto ti = _targets.find(targetFunctionName);
  if (ci == _constraints.end() || ti == _targets.end()) {
    // TODO: exception
  }
  ci->second->add(ti->second);
}

void ccgo::Optimizer::setParameters(const std::string& name,
				    const Eigen::VectorXd& params) {
  auto it = _targets.find(name);
  if (it == _targets.end()) {
    // TODO: exception
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


void ccgo::Optimizer::enableConstraint(const std::string& name) {
  auto it = _constraints.find(name);
  if (it != _constraints.end()) {
    if (!it->second->isEnabled()) {
      it->second->enable();
    }
  } else {
    // TODO: exception
  }
}

void ccgo::Optimizer::disableConstraint(const std::string& name) {
  auto it = _constraints.find(name);
  if (it != _constraints.end()) {
    if (it->second->isEnabled()) {
      it->second->disable();
    }
  } else {
    // TODO: exception
  }
}

void ccgo::Optimizer::enableTarget(const std::string& name) {
  auto it = _targets.find(name);
  if (it != _targets.end()) {
    if (!it->second->isEnabled()) {
      it->second->enable();
      // TODO : disable some of corresponding constraints
    }
  } else {
    // TODO: exception
  }
}

void ccgo::Optimizer::disableTarget(const std::string& name) {
  auto it = _targets.find(name);
  if (it != _targets.end()) {
    if (it->second->isEnabled()) {
      it->second->disable();
      // TODO: ? enable some of corresponding constraints
    }
  } else {
    // TODO: exception
  }
}

bool ccgo::Optimizer::optimize() {
  return false;
}
