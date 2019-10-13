#ifndef __CCGO_TESTCONSTRAINT_HPP__
#define __CCGO_TESTCONSTRAINT_HPP__
#include "Constraint.hpp"

namespace ccgo {
  class TestConstraint : public Constraint {
  public:
    TestConstraint(const std::string&, const double&);
    virtual ~TestConstraint();
    double getA() const;
  protected:
    double h(const Eigen::VectorXd&) const;
    Eigen::VectorXd dh(const Eigen::VectorXd&) const;
    Eigen::MatrixXd d2h(const Eigen::VectorXd&) const;
  private:
    double _a;
  };
}

#endif
