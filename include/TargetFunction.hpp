#ifndef __CCGO_TARGETFUNCTION_HPP__
#define __CCGO_TARGETFUNCTION_HPP__
#include <utility>
#include <vector>
#include "Function.hpp"
#include "ParamContainer.hpp"

namespace ccgo {
  class TargetFunction : public Function, public ParamContainer {
  public:
    TargetFunction(const std::string&, const long&);
    virtual ~TargetFunction();
    virtual double f(const Eigen::VectorXd&) const = 0;
    virtual Eigen::VectorXd df(const Eigen::VectorXd&) const = 0;
    virtual Eigen::MatrixXd d2f(const Eigen::VectorXd&) const = 0;
    virtual double getTargetValue() const;
    virtual double getTargetValue(const Eigen::VectorXd&) const;
    virtual void onFitBegin(const Eigen::VectorXd&) = 0;
    virtual void onFitEnd(const Eigen::VectorXd&) = 0;
  };
};

#endif
