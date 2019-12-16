#ifndef __CCGO_CONSTRAINT_HPP__
#define __CCGO_CONSTRAINT_HPP__
#include <unordered_map>

#include "Function.hpp"
#include "Switch.hpp"
#include "TargetFunction.hpp"

namespace ccgo {
class Constraint : public Function, public Switch {
 public:
  explicit Constraint(const std::string&);
  virtual ~Constraint();
  virtual double f(const Eigen::VectorXd&) const = 0;
  virtual Eigen::VectorXd df(const Eigen::VectorXd&) const = 0;
  virtual Eigen::MatrixXd d2f(const Eigen::VectorXd&) const = 0;
  virtual void add(const TargetFunction*);
  const std::unordered_map<std::string, const TargetFunction*>& getTargets()
      const;
  std::unordered_map<std::string, const TargetFunction*>& getTargets();

 protected:
  std::unordered_map<std::string, const TargetFunction*> _targets;
};
}  // namespace ccgo

#endif
