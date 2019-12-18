#ifndef __CCGO_OPTIMIZER_HPP__
#define __CCGO_OPTIMIZER_HPP__
#include <set>

#include "CommonParams.hpp"
#include "Constraint.hpp"
#include "TargetFunction.hpp"

namespace ccgo {
class Optimizer {
 public:
  Optimizer(long = 20, double = 1.e-3);
  virtual ~Optimizer();
  long getN() const;
  int getErrorCode() const;
  double getTargetValue() const;
  double getTargetValue(const std::string&) const;
  double getTargetValue(const std::set<std::string>&) const;
  const Eigen::VectorXd& getInitialParameters(const std::string&) const
      noexcept(false);
  const Eigen::VectorXd& getFinalParameters(const std::string&) const
      noexcept(false);
  std::unordered_map<std::string, CommonParams*>& getCommonParameters();
  const CommonParams* getCommonParameters(const std::string&) const;
  int getNumberOfEnabledTargets() const;
  int getNumberOfEnabledConstraints() const;
  int getNumberOfEnabledCommonParamContainers() const;
  double getConstant(const std::string&) const;
  void addTarget(TargetFunction*) noexcept(false);
  void addConstraint(Constraint*) noexcept(false);
  void addCommonParams(CommonParams*) noexcept(false);
  void addTargetToConstraint(const std::string&,
                             const std::string&) noexcept(false);
  void setParameters(const std::string&,
                     const Eigen::VectorXd&) noexcept(false);
  void setCommonParameters(const std::string&,
                           const Eigen::VectorXd&) noexcept(false);
  void setConstant(const std::string&, double) noexcept(false);
  void enableConstraint(const std::string&) noexcept(false);
  void disableConstraint(const std::string&) noexcept(false);
  void enableTarget(const std::string&) noexcept(false);
  void disableTarget(const std::string&) noexcept(false);
  void enableCommonParams(const std::string&) noexcept(false);
  void disableCommonParams(const std::string&) noexcept(false);
  void optimize();

 private:
  double calcTargetValue(const Eigen::VectorXd&) const;
  double f(const Eigen::VectorXd&) const;
  Eigen::VectorXd df(const Eigen::VectorXd&) const;
  Eigen::MatrixXd d2f(const Eigen::VectorXd&) const;
  void decIndicies(long, long);
  Eigen::VectorXd getInitialParamVector() const;
  void checkPeriodical(Eigen::VectorXd*) const;
  void onFitBegin(const Eigen::VectorXd&);
  void onFitEnd(const Eigen::VectorXd&);
  long _n;
  int _nIter;
  double _tol;
  double _targetValue;
  int _errorCode;
  std::unordered_map<std::string, TargetFunction*> _targets;
  std::unordered_map<std::string, Constraint*> _constraints;
  std::unordered_map<std::string, CommonParams*> _commonParams;
  std::unordered_map<std::string, double> _constants;
};
}  // namespace ccgo

#endif
