/*
 * CCGO optimizer
 * See LICENSE file at the top of the source tree.
 *
 * This product includes software developed by the
 * CMD-3 collaboration (https://cmd.inp.nsk.su/).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 */

/**
 * @file NameException.cpp
 *
 * @brief Implementation of NameException methods
 *
 * @ingroup ccgo
 *
 * @author Sergei Gribanov
 * Contact: ssgribanov@gmail.com
 *
 */

#include "NameException.hpp"

template <class T>
ccgo::NameException<T>::NameException(const std::string& name) : _name(name) {}

template <class T>
ccgo::NameException<T>::~NameException() {}

template <>
std::string ccgo::NameException<ccgo::TargetFunction>::what() const {
  std::string result = "[ERROR] There is no target function with such name: ";
  result.append(_name);
  return result;
}

template <>
std::string ccgo::NameException<ccgo::Constraint>::what() const {
  std::string result = "[ERROR] There is no constraint with such name: ";
  result.append(_name);
  return result;
}

template <>
std::string ccgo::NameException<ccgo::CommonParams>::what() const {
  std::string result =
      "[ERROR] There is no common params container with such name: ";
  result.append(_name);
  return result;
}
