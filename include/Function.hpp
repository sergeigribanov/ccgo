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
    std::unordered_map<std::string, CommonParams*>* getCommonParameters() const;
    std::unordered_map<std::string, double>* getConstants() const;
    void setCommonParameters(std::unordered_map<std::string, CommonParams*>*);
    void setConstants(std::unordered_map<std::string, double>*);
  private:
    std::string _name;
    std::unordered_map<std::string, CommonParams*>* _commonParams;
    std::unordered_map<std::string, double>* _constants;
  };
}

#endif
