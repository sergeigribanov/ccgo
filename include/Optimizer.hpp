#ifndef __CCGO_OPTIMIZER_HPP__
#define __CCGO_OPTIMIZER_HPP__
#include "TargetFunction.hpp"
#include "Constraint.hpp"

namespace ccgo {
  class Optimizer {
  public:
    Optimizer();
    virtual ~Optimizer();
    long getN() const;
    long getNTotal() const;
    const Eigen::VectorXd& getInitialParameters(const std::string&) const noexcept(false);
    const Eigen::VectorXd& getFinalParameters(const std::string&) const noexcept(false);
    void addTarget(TargetFunction*) noexcept(false);
    void addConstraint(Constraint*) noexcept(false);
    void addTargetToConstraint(const std::string&, const std::string&) noexcept(false);
    void setParameters(const std::string&, const Eigen::VectorXd&) noexcept(false);
    void enableConstraint(const std::string&) noexcept(false);
    void disableConstraint(const std::string&) noexcept(false);
    void enableTarget(const std::string&) noexcept(false);
    void disableTarget(const std::string&) noexcept(false);
    int optimize();
    double f(const Eigen::VectorXd&) const;
    Eigen::VectorXd df(const Eigen::VectorXd&) const;
  private:
    Eigen::MatrixXd d2f(const Eigen::VectorXd&) const;
    void incLambdaIndexes(const long&);
    void decLambdaIndexes(const long&);
    void decLambdaIndexesByOne(const long&);
    Eigen::VectorXd getInitialParamVector() const;
    void onFitBegin(const Eigen::VectorXd&);
    void onFitEnd(const Eigen::VectorXd&);
    long _n;
    long _nTotal;
    int _nIter;
    double _tol;
    std::unordered_map<std::string, TargetFunction*> _targets;
    std::unordered_map<std::string, Constraint*> _constraints;
  };
}

#endif
