#ifndef __NAME_EXCEPTION_HPP__
#define __NAME_EXCEPTION_HPP__
#include <string>

#include "CommonParams.hpp"
#include "Constraint.hpp"
#include "TargetFunction.hpp"

namespace ccgo {

template <class T>
class NameException {
 public:
  explicit NameException(const std::string&);
  virtual ~NameException();
  std::string what() const;

 private:
  std::string _name;
};

template class NameException<TargetFunction>;
template class NameException<Constraint>;
template class NameException<CommonParams>;
}  // namespace ccgo
#endif
