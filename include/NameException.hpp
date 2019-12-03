#ifndef __NAME_EXCEPTION_HPP__
#define __NAME_EXCEPTION_HPP__
#include <string>
#include "TargetFunction.hpp"
#include "Constraint.hpp"
#include "CommonParams.hpp"

namespace ccgo {

  template<class T>
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
}
#endif
