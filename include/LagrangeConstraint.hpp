#ifndef __CCGO_LAGRANGE_CONSTRAINT_HPP__
#define __CCGO_LAGRANGE_CONSTRAINT_HPP__
#include "Constraint.hpp"

namespace ccgo {
  class LagrangeConstraint : public Constraint {
  public:
    explicit LagrangeConstraint(const std::string&);
    virtual ~LagrangeConstraint();
    virtual double f(const Eigen::VectorXd&) const override final;
    virtual Eigen::VectorXd df(const Eigen::VectorXd&) const override final;
    virtual Eigen::MatrixXd d2f(const Eigen::VectorXd&) const override final;
    long getLambdaIndex() const;
    double getLambdaInitial() const;
    double getLambdaFinal() const;
    void setLambdaIndex(const long&);
    void setLambdaInitial(const double&);
    void setLambdaFinal(const Eigen::VectorXd&);
  protected:
    std::unordered_map<std::string, const TargetFunction*> _targets;
    virtual double h(const Eigen::VectorXd&) const = 0;
    virtual Eigen::VectorXd dh(const Eigen::VectorXd&) const = 0;
    virtual Eigen::MatrixXd d2h(const Eigen::VectorXd&) const = 0;
  private:
    long _lambdaIndex;
    double _lambdaInitial;
    double _lambdaFinal;
  };
}

#endif
