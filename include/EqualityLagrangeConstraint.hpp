#ifndef __CCGO_EQUALITY_LAGRANGE_CONSTRAINT_HPP__
#define __CCGO_EQUALITY_LAGRANGE_CONSTRAINT_HPP__
#include "LagrangeConstraint.hpp"

namespace ccgo {
  class EqualityLagrangeConstraint : public LagrangeConstraint {
  public:
    explicit EqualityLagrangeConstraint(const std::string&);
    virtual ~EqualityLagrangeConstraint();
    virtual double f(const Eigen::VectorXd&) const override final;
    virtual Eigen::VectorXd df(const Eigen::VectorXd&) const override final;
    virtual Eigen::MatrixXd d2f(const Eigen::VectorXd&) const override final;
  protected:
    virtual double h(const Eigen::VectorXd&) const override = 0;
    virtual Eigen::VectorXd dh(const Eigen::VectorXd&) const override = 0;
    virtual Eigen::MatrixXd d2h(const Eigen::VectorXd&) const override = 0;
  };
}

#endif
