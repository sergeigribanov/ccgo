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
    const Eigen::VectorXd& getInitialParameters(const std::string&) const;
    const Eigen::VectorXd& getFinalParameters(const std::string&) const;
    void addTarget(TargetFunction*);
    void addConstraint(Constraint*);
    void addTargetToConstraint(const std::string&, const std::string&);
    void setParameters(const std::string&, const Eigen::VectorXd&);
    void enableConstraint(const std::string&);
    void disableConstraint(const std::string&);
    void enableTarget(const std::string&);
    void disableTarget(const std::string&);
    bool optimize();
  private:
    long _n;
    long _nTotal;
    double f(const Eigen::VectorXd&) const;
    Eigen::VectorXd df(const Eigen::VectorXd&) const;
    Eigen::MatrixXd d2f(const Eigen::VectorXd&) const;
    std::unordered_map<std::string, TargetFunction*> _targets;
    std::unordered_map<std::string, Constraint*> _constraints;
  };
}

#endif
