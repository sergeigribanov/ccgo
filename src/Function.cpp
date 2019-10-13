#include "Function.hpp"

ccgo::Function::Function(const std::string& name):
  _enabled(false),
  _name(name) {
}

ccgo::Function::~Function() {
}

bool ccgo::Function::isEnabled() const {
  return _enabled;
}

std::string ccgo::Function::getName() const {
  return _name;
}

void ccgo::Function::enable() {
  _enabled = true;
}

void ccgo::Function::disable() {
  _enabled = false;
}
