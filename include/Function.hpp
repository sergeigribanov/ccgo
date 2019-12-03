#ifndef __CCGO_FUNCTION_HPP__
#define __CCGO_FUNCTION_HPP__
#include <string>
#include <Eigen/Dense>
#include "CommonParams.hpp"

namespace ccgo {
  class Function {
  public:
    explicit Function(const std::string&);
    virtual ~Function();
    std::string getName() const;
    virtual double f(const Eigen::VectorXd&) const = 0;
    virtual Eigen::VectorXd df(const Eigen::VectorXd&) const = 0;
    virtual Eigen::MatrixXd d2f(const Eigen::VectorXd&) const = 0;
    const std::unordered_map<std::string, CommonParams*>* getCommonParameters() const;
    void setCommonParameters(const std::unordered_map<std::string, CommonParams*>*);
  private:
    std::string _name;
    const std::unordered_map<std::string, CommonParams*>* _commonParams;
  };
}

#endif
