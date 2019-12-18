#include "Optimizer.hpp"

#include <math.h>

#include <iostream>
#include <limits>
#include <utility>

#include "LagrangeConstraint.hpp"
#include "NameException.hpp"

ccgo::Optimizer::Optimizer(long nIter, double tolerance)
    : _n(0),
      _nTotal(0),
      _nIter(nIter),
      _tol(tolerance),
      _targetValue(std::numeric_limits<double>::infinity()),
      _errorCode(1) {}

ccgo::Optimizer::~Optimizer() {}

long ccgo::Optimizer::getN() const { return _n; }

long ccgo::Optimizer::getNTotal() const { return _nTotal; }

int ccgo::Optimizer::getErrorCode() const { return _errorCode; }

double ccgo::Optimizer::getTargetValue() const { return _targetValue; }

double ccgo::Optimizer::getTargetValue(
    const std::set<std::string>& targetNames) const {
  double result = 0;
  for (const auto& name : targetNames) {
    const auto& target = _targets.at(name);
    if (target->isEnabled()) {
      result += target->getTargetValue();
    } else {
      // TO DO: exception
    }
  }
  return result;
}

const Eigen::VectorXd& ccgo::Optimizer::getInitialParameters(
    const std::string& name) const noexcept(false) {
  auto it = _targets.find(name);
  if (it == _targets.end()) {
    ccgo::NameException<ccgo::TargetFunction> e(name);
    std::cerr << e.what() << std::endl;
    throw(e);
  }
  return it->second->getInitialParameters();
}

const Eigen::VectorXd& ccgo::Optimizer::getFinalParameters(
    const std::string& name) const noexcept(false) {
  auto it = _targets.find(name);
  if (it == _targets.end()) {
    ccgo::NameException<ccgo::TargetFunction> e(name);
    std::cerr << e.what() << std::endl;
    throw(e);
  }
  return it->second->getFinalParameters();
}

void ccgo::Optimizer::addTarget(ccgo::TargetFunction* obj) noexcept(false) {
  if (_targets.find(obj->getName()) == _targets.end()) {
    obj->setCommonParameters(&_commonParams);
    obj->setConstants(&_constants);
    _targets.insert(std::make_pair(obj->getName(), obj));
  } else {
    ccgo::NameException<ccgo::TargetFunction> e(obj->getName());
    std::cerr << e.what() << std::endl;
    throw(e);
  }
}

void ccgo::Optimizer::addConstraint(ccgo::Constraint* obj) noexcept(false) {
  if (_constraints.find(obj->getName()) == _constraints.end()) {
    obj->setCommonParameters(&_commonParams);
    obj->setConstants(&_constants);
    _constraints.insert(std::make_pair(obj->getName(), obj));
  } else {
    ccgo::NameException<ccgo::Constraint> e(obj->getName());
    std::cerr << e.what() << std::endl;
    throw(e);
  }
}

void ccgo::Optimizer::addTargetToConstraint(
    const std::string& targetFunctionName,
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

void ccgo::Optimizer::setParameters(
    const std::string& name, const Eigen::VectorXd& params) noexcept(false) {
  auto it = _targets.find(name);
  if (it == _targets.end()) {
    ccgo::NameException<ccgo::TargetFunction> e(name);
    std::cerr << e.what() << std::endl;
    throw(e);
  }
  it->second->setInitialParameters(params);
}

double ccgo::Optimizer::calcTargetValue(const Eigen::VectorXd& x) const {
  double result = 0;
  for (const auto& el : _targets) {
    if (el.second->isEnabled()) {
      result += el.second->getTargetValue(x);
    }
  }
  return result;
}

double ccgo::Optimizer::f(const Eigen::VectorXd& x) const {
  double result = 0;
  for (const auto& el : _targets) {
    if (el.second->isEnabled()) {
      result += el.second->f(
          x.segment(el.second->getBeginIndex(), el.second->getN()));
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
  Eigen::VectorXd result = Eigen::VectorXd::Zero(_nTotal);
  for (const auto& el : _targets) {
    if (el.second->isEnabled()) {
      result.segment(el.second->getBeginIndex(), el.second->getN()) +=
          el.second->df(
              x.segment(el.second->getBeginIndex(), el.second->getN()));
    }
  }
  for (const auto& el : _constraints) {
    if (el.second->isEnabled()) {
      result += el.second->df(x);
    }
  }
  for (const auto& el : _targets) {
    if (el.second->isEnabled()) {
      for (long index : el.second->getFixedParamIndexes()) {
        long idx = el.second->getBeginIndex() + index;
        result(idx) = 0;
      }
    }
  }
  for (const auto& el : _commonParams) {
    if (el.second->isEnabled()) {
      for (long index : el.second->getFixedParamIndexes()) {
        long idx = el.second->getBeginIndex() + index;
        result(idx) = 0;
      }
    }
  }
  return result;
}

Eigen::MatrixXd ccgo::Optimizer::d2f(const Eigen::VectorXd& x) const {
  Eigen::MatrixXd result = Eigen::MatrixXd::Zero(_nTotal, _nTotal);
  for (const auto& el : _targets) {
    if (el.second->isEnabled()) {
      result.block(el.second->getBeginIndex(), el.second->getBeginIndex(),
                   el.second->getN(), el.second->getN()) +=
          el.second->d2f(
              x.segment(el.second->getBeginIndex(), el.second->getN()));
    }
  }
  for (const auto& el : _constraints) {
    if (el.second->isEnabled()) {
      result += el.second->d2f(x);
    }
  }
  for (const auto& el : _targets) {
    if (el.second->isEnabled()) {
      for (long index : el.second->getFixedParamIndexes()) {
        long idx = el.second->getBeginIndex() + index;
        result.row(idx).setZero();
        result.col(idx).setZero();
        result(idx, idx) = 1;
      }
    }
  }
  for (const auto& el : _commonParams) {
    if (el.second->isEnabled()) {
      for (long index : el.second->getFixedParamIndexes()) {
        long idx = el.second->getBeginIndex() + index;
        result.row(idx).setZero();
        result.col(idx).setZero();
        result(idx, idx) = 1;
      }
    }
  }
  return result;
}

void ccgo::Optimizer::enableConstraint(const std::string& name) noexcept(
    false) {
  auto it = _constraints.find(name);
  if (it != _constraints.end()) {
    if (!it->second->isEnabled()) {
      it->second->enable();
      auto lc = dynamic_cast<ccgo::LagrangeConstraint*>(it->second);
      if (lc) {
        lc->setLambdaIndex(_nTotal);
        _nTotal += 1;
      }
    }
  } else {
    ccgo::NameException<ccgo::Constraint> e(name);
    std::cerr << e.what() << std::endl;
    throw(e);
  }
}

void ccgo::Optimizer::disableConstraint(const std::string& name) noexcept(
    false) {
  auto it = _constraints.find(name);
  if (it != _constraints.end()) {
    if (it->second->isEnabled()) {
      it->second->disable();
      auto lc = dynamic_cast<ccgo::LagrangeConstraint*>(it->second);
      if (lc) {
        _nTotal -= 1;
        decLambdaIndexesByOne(lc->getLambdaIndex());
      }
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

void ccgo::Optimizer::checkPeriodical(Eigen::VectorXd* x) const {
  for (const auto& el : _targets) {
    if (el.second->isEnabled() && el.second->havePeriodical()) {
      el.second->checkPeriodical(x);
    }
  }
  for (const auto& el : _commonParams) {
    if (el.second->isEnabled() && el.second->havePeriodical()) {
      el.second->checkPeriodical(x);
    }
  }
}

void ccgo::Optimizer::optimize() {
  Eigen::VectorXd x = getInitialParamVector();
  onFitBegin(x);
  Eigen::VectorXd xp;
  for (int i = 0; i < _nIter; ++i) {
    xp = x;
    x -= d2f(x).inverse() * df(x);
    checkPeriodical(&x);
    if (fabs(f(x) - f(xp)) < _tol) {
      onFitEnd(x);
      _errorCode = 0;
      return;
    }
  }
  onFitEnd(x);
  _errorCode = 1;
  return;
}

void ccgo::Optimizer::onFitBegin(const Eigen::VectorXd& x) {
  for (auto& el : _targets) {
    if (el.second->isEnabled()) {
      el.second->onFitBegin(x);
    }
  }
}

void ccgo::Optimizer::onFitEnd(const Eigen::VectorXd& x) {
  for (auto& el : _targets) {
    if (el.second->isEnabled()) {
      el.second->setFinalParameters(x);
      el.second->onFitEnd(x);
    }
  }
  for (auto& el : _commonParams) {
    if (el.second->isEnabled()) {
      el.second->setFinalParameters(x);
    }
  }
  for (auto& el : _constraints) {
    if (el.second->isEnabled()) {
      auto lc = dynamic_cast<ccgo::LagrangeConstraint*>(el.second);
      if (lc) {
        lc->setLambdaFinal(x);
      }
    }
  }
  _targetValue = calcTargetValue(x);
}

void ccgo::Optimizer::incLambdaIndexes(const long& n) {
  for (auto& el : _constraints) {
    if (el.second->isEnabled()) {
      auto lc = dynamic_cast<ccgo::LagrangeConstraint*>(el.second);
      if (lc) {
        lc->setLambdaIndex(lc->getLambdaIndex() + n);
      }
    }
  }
}

void ccgo::Optimizer::decLambdaIndexes(const long& n) {
  for (auto& el : _constraints) {
    if (el.second->isEnabled()) {
      auto lc = dynamic_cast<ccgo::LagrangeConstraint*>(el.second);
      if (lc) {
        lc->setLambdaIndex(lc->getLambdaIndex() - n);
      }
    }
  }
}

void ccgo::Optimizer::decLambdaIndexesByOne(const long& index) {
  for (auto& el : _constraints) {
    if (el.second->isEnabled()) {
      auto lc = dynamic_cast<ccgo::LagrangeConstraint*>(el.second);
      if (lc) {
        if (lc->getLambdaIndex() > index) {
          lc->setLambdaIndex(lc->getLambdaIndex() - 1);
        }
      }
    }
  }
}

Eigen::VectorXd ccgo::Optimizer::getInitialParamVector() const {
  Eigen::VectorXd result(_nTotal);
  for (const auto& el : _targets) {
    if (el.second->isEnabled()) {
      result.segment(el.second->getBeginIndex(), el.second->getN()) =
          el.second->getInitialParameters();
    }
  }
  for (const auto& el : _commonParams) {
    if (el.second->isEnabled()) {
      result.segment(el.second->getBeginIndex(), el.second->getN()) =
          el.second->getInitialParameters();
    }
  }
  for (const auto& el : _constraints) {
    if (el.second->isEnabled()) {
      auto lc = dynamic_cast<ccgo::LagrangeConstraint*>(el.second);
      if (lc) {
        result(lc->getLambdaIndex()) = lc->getLambdaInitial();
      }
    }
  }
  return result;
}

void ccgo::Optimizer::addCommonParams(ccgo::CommonParams* obj) noexcept(false) {
  if (_commonParams.find(obj->getName()) == _commonParams.end()) {
    _commonParams.insert(std::make_pair(obj->getName(), obj));
  } else {
    ccgo::NameException<ccgo::CommonParams> e(obj->getName());
    std::cerr << e.what() << std::endl;
    throw(e);
  }
}

void ccgo::Optimizer::setCommonParameters(
    const std::string& name, const Eigen::VectorXd& params) noexcept(false) {
  auto it = _commonParams.find(name);
  if (it == _commonParams.end()) {
    ccgo::NameException<ccgo::TargetFunction> e(name);
    std::cerr << e.what() << std::endl;
    throw(e);
  }
  it->second->setInitialParameters(params);
}

void ccgo::Optimizer::enableCommonParams(const std::string& name) noexcept(
    false) {
  auto it = _commonParams.find(name);
  if (it != _commonParams.end()) {
    if (!it->second->isEnabled()) {
      it->second->enable();
      it->second->setBeginIndex(_n);
      _n += it->second->getN();
      _nTotal += it->second->getN();
      incLambdaIndexes(it->second->getN());
    }
  } else {
    ccgo::NameException<ccgo::CommonParams> e(name);
    std::cerr << e.what() << std::endl;
    throw(e);
  }
}

void ccgo::Optimizer::disableCommonParams(const std::string& name) noexcept(
    false) {
  auto it = _commonParams.find(name);
  if (it != _commonParams.end()) {
    if (it->second->isEnabled()) {
      it->second->disable();
      _n -= it->second->getN();
      _nTotal -= it->second->getN();
      decLambdaIndexes(it->second->getN());
    }
  } else {
    ccgo::NameException<ccgo::CommonParams> e(name);
    std::cerr << e.what() << std::endl;
    throw(e);
  }
}

std::unordered_map<std::string, ccgo::CommonParams*>&
ccgo::Optimizer::getCommonParameters() {
  return _commonParams;
}

const ccgo::CommonParams* ccgo::Optimizer::getCommonParameters(
    const std::string& name) const {
  return _commonParams.at(name);
}

double ccgo::Optimizer::getConstant(const std::string& name) const {
  return _constants.at(name);
}

void ccgo::Optimizer::setConstant(const std::string& name,
                                  double value) noexcept(false) {
  _constants.insert(std::make_pair(name, value));
}
