#ifndef __CCGO_TARGETFUNCTION_HPP__
#define __CCGO_TARGETFUNCTION_HPP__
#include "Function.hpp"

namespace ccgo {
  class TargetFunction : public Function {
  public:
    TargetFunction(const std::string&, const long&);
    virtual ~TargetFunction();
    long getBeginIndex() const;
    long getN() const;
    long getEndIndex() const;
    const Eigen::VectorXd& getInitialParameters() const;
    const Eigen::VectorXd& getFinalParameters() const;
    double f(const Eigen::VectorXd&) const;
    Eigen::VectorXd df(const Eigen::VectorXd&) const;
    Eigen::MatrixXd d2f(const Eigen::VectorXd&) const;
    double getTargetValue() const;
    void setInitialParameters(const Eigen::VectorXd&);
    void setBeginIndex(const long&);
    void setFinalParameters(const Eigen::VectorXd&);
    virtual void onFitBegin(const Eigen::VectorXd&) = 0;
    virtual void onFitEnd(const Eigen::VectorXd&) = 0;
  protected:
    virtual double ownf(const Eigen::VectorXd&) const = 0;
    virtual Eigen::VectorXd owndf(const Eigen::VectorXd&) const = 0;
    virtual Eigen::MatrixXd ownd2f(const Eigen::VectorXd&) const = 0;
    Eigen::VectorXd _xInitial;
    Eigen::VectorXd _xFinal;
  private:
    long _beginIndex;
  };
};

#endif
