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
    virtual void onFitBegin(const Eigen::VectorXd&) override;
    virtual void onFitEnd(const Eigen::VectorXd&) override;
  protected:
    double ownf(const Eigen::VectorXd&) const;
    virtual Eigen::VectorXd owndf(const Eigen::VectorXd&) const override final;
    virtual Eigen::MatrixXd ownd2f(const Eigen::VectorXd&) const override final;
  private:
    Eigen::MatrixXd _inverseErrorMatrix;
  };
}

#endif
