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
  virtual double f(const Eigen::VectorXd&) const override final;
  virtual Eigen::VectorXd df(const Eigen::VectorXd&) const override final;
  virtual Eigen::MatrixXd d2f(const Eigen::VectorXd&) const override final;
  virtual void onFitBegin(const Eigen::VectorXd&) override;
  virtual void onFitEnd(const Eigen::VectorXd&) override;

 private:
  Eigen::MatrixXd _inverseErrorMatrix;
};
}  // namespace ccgo

#endif
