#include "Constraint.hpp"

#include <iostream>
#include <utility>

ccgo::Constraint::Constraint(const std::string& name) : Function(name) {}

ccgo::Constraint::~Constraint() {}

void ccgo::Constraint::add(const ccgo::TargetFunction* obj) {
  if (_targets.find(obj->getName()) == _targets.end()) {
    _targets.insert(std::make_pair(obj->getName(), obj));
  } else {
    // TODO: exception
  }
}

const std::unordered_map<std::string, const ccgo::TargetFunction*>&
ccgo::Constraint::getTargets() const {
  return _targets;
}

std::unordered_map<std::string, const ccgo::TargetFunction*>&
ccgo::Constraint::getTargets() {
  return _targets;
}
