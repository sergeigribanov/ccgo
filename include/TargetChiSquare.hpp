#ifndef __CCGO_TARGETCHISQUARE_HPP__
#define __CCGO_TARGETCHISQUARE_HPP__
#include "TargetFunction.hpp"

namespace ccgo {
  class TargetChiSquare : public TargetFunction {
  public:
    TargetChiSquare(const std::string&, const long&);
    virtual ~TargetChiSquare();
    const Eigen::MatrixXd& getInverseErrorMatrix() const;
    void setInverseErrorMatrix(const Eigen::MatrixXd&);
  protected:
    double ownf(const Eigen::VectorXd&) const;
    Eigen::VectorXd owndf(const Eigen::VectorXd&) const;
    Eigen::MatrixXd ownd2f(const Eigen::VectorXd&) const;
  private:
    Eigen::MatrixXd _inverseErrorMatrix;
  };
}

#endif
