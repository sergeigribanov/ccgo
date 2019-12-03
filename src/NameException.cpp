#include "NameException.hpp"

template<class T>
ccgo::NameException<T>::NameException(const std::string& name):
  _name(name) {
}

template<class T>
ccgo::NameException<T>::~NameException() {
}

template<>
std::string ccgo::NameException<ccgo::TargetFunction>::what() const {
  std::string result = "[ERROR] There is no target function with such name: ";
  result.append(_name);
  return result;
}

template<>
std::string ccgo::NameException<ccgo::Constraint>::what() const {
  std::string result = "[ERROR] There is no constraint with such name: ";
  result.append(_name);
  return result;
}

template<>
std::string ccgo::NameException<ccgo::CommonParams>::what() const {
  std::string result = "[ERROR] There is no common params container with such name: ";
  result.append(_name);
  return result;
}
