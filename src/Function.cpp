#include "Function.hpp"

ccgo::Function::Function(const std::string& name):
  _name(name) {
}

ccgo::Function::~Function() {
}

std::string ccgo::Function::getName() const {
  return _name;
}

const std::unordered_map<std::string, ccgo::CommonParams*>*
ccgo::Function::getCommonParameters() const {
  return _commonParams;
}

void ccgo::Function::setCommonParameters
(const std::unordered_map<std::string, CommonParams*>* params) {
  _commonParams = params;
}
