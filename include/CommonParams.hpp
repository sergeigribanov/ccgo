#ifndef __CCGO_COMMONPARAMS_HPP__
#define __CCGO_COMMONPARAMS_HPP__
#include <string>

#include "ParamContainer.hpp"
#include "Switch.hpp"

namespace ccgo {
class CommonParams : public ParamContainer, public Switch {
 public:
  CommonParams(const std::string&, const long&);
  virtual ~CommonParams();
  std::string getName() const;

 private:
  std::string _name;
};
}  // namespace ccgo

#endif
