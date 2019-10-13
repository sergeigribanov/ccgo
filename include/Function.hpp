#ifndef __CCGO_FUNCTION_HPP__
#define __CCGO_FUNCTION_HPP__
#include <string>
#include <Eigen/Dense>

namespace ccgo {
  class Function {
  public:
    explicit Function(const std::string&);
    virtual ~Function();
    bool isEnabled() const;
    std::string getName() const;
    virtual double f(const Eigen::VectorXd&) const = 0;
    virtual Eigen::VectorXd df(const Eigen::VectorXd&) const = 0;
    virtual Eigen::MatrixXd d2f(const Eigen::VectorXd&) const = 0;
    void enable();
    void disable();
  private:
    bool _enabled;
    std::string _name;
  };
}

#endif
