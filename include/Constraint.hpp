#ifndef __CCGO_CONSTRAINT_HPP__
#define __CCGO_CONSTRAINT_HPP__
#include <unordered_map>
#include "Function.hpp"
#include "TargetFunction.hpp"

namespace ccgo {
  class Constraint : public Function {
  public:
    explicit Constraint(const std::string&);
    virtual ~Constraint();
    double f(const Eigen::VectorXd&) const;
    Eigen::VectorXd df(const Eigen::VectorXd&) const;
    Eigen::MatrixXd d2f(const Eigen::VectorXd&) const;
    long getLambdaIndex() const;
    double getLambdaInitial() const;
    double getLambdaFinal() const;
    void setLambdaIndex(const long&);
    void setLambdaInitial(const double&);
    void setLambdaFinal(const Eigen::VectorXd&);
    void add(const TargetFunction*);
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
