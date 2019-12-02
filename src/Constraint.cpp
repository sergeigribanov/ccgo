#include <utility>
#include <iostream>
#include "Constraint.hpp"

ccgo::Constraint::Constraint(const std::string& name) :
  Function(name) {
}

ccgo::Constraint::~Constraint() {
}

void ccgo::Constraint::add(const TargetFunction* obj) {
  if (_targets.find(obj->getName()) == _targets.end()) {
    _targets.insert(std::make_pair(obj->getName(), obj));
  } else {
    // TODO: exception
  }
}
