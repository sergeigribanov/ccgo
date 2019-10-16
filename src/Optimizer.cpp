#include <utility>
#include <iostream>
#include <math.h>
#include "NameException.hpp"
#include "Optimizer.hpp"

ccgo::Optimizer::Optimizer():
  _n(0), _nTotal(0),
  _nIter(100), _nIterLS(1000),
  _tol(1.e-12), _tolLS(1.e-12),
  beta(ccgo::Optimizer::betaByName(ccgo::FLETCHER_REEVES)) {
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
    // obj->setBeginIndex(_n);
    // _n += obj->getN();
    // _nTotal += obj->getN();
    // incLambdaIndexes(obj->getN());
  } else {
    ccgo::NameException<TargetFunction> e(obj->getName());
    std::cerr << e.what() << std::endl;
    throw(e);
  }
}

void ccgo::Optimizer::addConstraint(Constraint* obj) noexcept(false) {
  if (_constraints.find(obj->getName()) == _constraints.end()) {
    _constraints.insert(std::make_pair(obj->getName(), obj));
    // obj->setLambdaIndex(_nTotal);
    // _nTotal += 1;
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

int ccgo::Optimizer::optimize() {
  int lsflag;
  double w;
  double lam;
  Eigen::VectorXd x = getInitialParamVector();
  Eigen::VectorXd xp;
  Eigen::VectorXd dx;
  Eigen::VectorXd ag;
  Eigen::VectorXd agp;
  Eigen::VectorXd s;
  for (int k = 0; k < _nIter; ++k) {
    agp = -df(x);
    s = agp;
    for (int j = 0; j < _nIter; ++j) {
      xp = x;
      lam = 0;
      lsflag = lsearch(x, s, &lam);
      x += lam * s;
      ag = -df(x);
      if (lsflag) {
	w = 0;
      } else {
	w = beta(agp, ag, s);
      }
      s = ag + w * s;
      agp = ag;
      dx = x - xp;
      if (s.transpose() * s < _tol || dx.transpose() * dx < _tol) {
	setFinalParameters(x);
	return 0;
      }
    }
  }
  setFinalParameters(x);
  return 1;
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

Eigen::VectorXd ccgo::Optimizer::getInitialParamVector() const {
  Eigen::VectorXd result(_nTotal);
  for (const auto& el : _targets) {
    if (el.second->isEnabled()) {
      result.block(el.second->getBeginIndex(), 0, el.second->getEndIndex(), 1) =
	el.second->getInitialParameters();
    } 
  }
  for (const auto& el : _constraints) {
    if (el.second->isEnabled()) {
      result(el.second->getLambdaIndex()) = el.second->getLambdaInitial();
    }
  }
  return result;
}

int ccgo::Optimizer::lsearch(const Eigen::VectorXd& x, const Eigen::VectorXd& s, double* lam) const {
  if (s.transpose() * s == 0) {
    return 0;
  }
  double up;
  double down;
  double del;
  Eigen::VectorXd dfVec;
  for (int i = 0; i < _nIterLS; ++i) {
    dfVec = df(x + (*lam) * s);
    if (dfVec.transpose() * dfVec == 0) {
      return 0;
    }
    up = s.transpose() * dfVec;
    Eigen::MatrixXd d2fM = d2f(x + (*lam) * s);
    down = s.transpose() * d2fM * s;
    del = up / down;
    *lam -= del;
    if (fabs(del) < _tolLS) {
      return 0;
    }
  }
  return 1;
}

double ccgo::Optimizer::beta_FLETCHER_REEVES(const Eigen::VectorXd& dxp,
					     const Eigen::VectorXd& dx,
					     const Eigen::VectorXd& sp) {
  return ((double)(dx.transpose() * dx)) / ((double)(dxp.transpose() * dxp));
}

double ccgo::Optimizer::beta_POLAK_RIBIERE(const Eigen::VectorXd& dxp,
					   const Eigen::VectorXd& dx,
					   const Eigen::VectorXd& sp) {
 double res = ((double)(dx.transpose() * (dx - dxp))) /
    ((double)(dxp.transpose() * dxp));
 return std::max(0., res);
}

double ccgo::Optimizer::beta_HESTENES_STIEFEL(const Eigen::VectorXd& dxp,
					      const Eigen::VectorXd& dx,
					      const Eigen::VectorXd& sp) {
  double res =  -((double)(dx.transpose() * (dx - dxp))) / ((double)(sp.transpose() * (dx - dxp)));
  return std::max(0., res);
}

double ccgo::Optimizer::beta_DAI_YUAN(const Eigen::VectorXd& dxp,
				      const Eigen::VectorXd& dx,
				      const Eigen::VectorXd& sp) {
  double res = -((double)(dx.transpose() * dx)) / ((double)(sp.transpose() * (dx - dxp)));
  return std::max(0., res);
}

ccgo::BetaWT ccgo::Optimizer::betaByName(const ccgo::STEP_WT& name) {
  switch (name) {
  case ccgo::FLETCHER_REEVES:
    return &ccgo::Optimizer::beta_FLETCHER_REEVES;
  case ccgo::POLAK_RIBIERE:
    return &ccgo::Optimizer::beta_POLAK_RIBIERE;
  case ccgo::HESTENES_STIEFEL:
    return &ccgo::Optimizer::beta_HESTENES_STIEFEL;
  case ccgo::DAI_YUAN:
    return &ccgo::Optimizer::beta_DAI_YUAN;
  default:
    return &ccgo::Optimizer::beta_DAI_YUAN;
  }
}

void ccgo::Optimizer::setFinalParameters(const Eigen::VectorXd& x) {
  for (auto& el : _targets) {
    if (el.second->isEnabled()) {
      el.second->setFinalParameters(x);
    }
  }
  for (auto& el : _constraints) {
    if (el.second->isEnabled()) {
      el.second->setLambdaFinal(x);
    }
  }
}
