#ifndef __CCGO_TESTCONSTRAINT_HPP__
#define __CCGO_TESTCONSTRAINT_HPP__
#include "EqualityLagrangeConstraint.hpp"

namespace ccgo {
  class TestConstraint : public EqualityLagrangeConstraint {
  public:
    TestConstraint(const std::string&, const double&);
    virtual ~TestConstraint();
    double getA() const;
  protected:
    virtual double h(const Eigen::VectorXd&) const override final;
    virtual Eigen::VectorXd dh(const Eigen::VectorXd&) const override final;
    virtual Eigen::MatrixXd d2h(const Eigen::VectorXd&) const override final;
  private:
    double _a;
  };
}

#endif
