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
 * @file Function.cpp
 *
 * @brief Implementation of Function methods
 *
 * @ingroup ccgo
 *
 * @author Sergei Gribanov
 * Contact: ssgribanov@gmail.com
 *
 */

#include "Function.hpp"

ccgo::Function::Function() {}

ccgo::Function::~Function() {}

std::unordered_map<std::string, ccgo::CommonParams*>*
ccgo::Function::getCommonParameters() const {
  return _commonParams;
}

void ccgo::Function::setCommonParameters(
					 std::unordered_map<std::string, CommonParams*>* params) {
  _commonParams = params;
}

void ccgo::Function::setConstants(
				  std::unordered_map<std::string, double>* constants) {
  _constants = constants;
}

std::unordered_map<std::string, double>* ccgo::Function::getConstants() const {
  return _constants;
}

Eigen::VectorXd ccgo::Function::dfNumerical(const Eigen::VectorXd& x, double h) const {
  Eigen::VectorXd result = Eigen::VectorXd::Zero(x.size());
  Eigen::VectorXd vh = Eigen::VectorXd::Zero(x.size());
  for (long index = 0; index < x.size(); ++index) {
    vh(index) = h;
    result(index) = 0.5 * (f(x + vh) - f(x - vh)) / h;
    vh(index) = 0;
  }
  return result;
}

Eigen::MatrixXd ccgo::Function::d2fNumerical(const Eigen::VectorXd& x, double h) const {
  Eigen::MatrixXd result = Eigen::MatrixXd::Zero(x.size(), x.size());
  Eigen::VectorXd vh0 = Eigen::VectorXd::Zero(x.size());
  Eigen::VectorXd vh1 = Eigen::VectorXd::Zero(x.size());
  for (long index0 = 0; index0 < x.size(); ++index0) {
    vh0(index0) = 0.5 * h;
    result(index0, index0) = (f(x + 2 * vh0) - 2 * f(x) + f(x - 2 * vh0)) / h / h;
    for (long index1 = index0 + 1; index1 < x.size(); ++index1) {
      vh1(index1) = 0.5 * h;
      result(index0, index1) = (f(x + vh0 + vh1) - f(x - vh0 + vh1) -
				f(x + vh0 - vh1) + f(x -vh0 - vh1)) / h / h;
      result(index1, index0) = result(index0, index1);
      vh1(index1) = 0;
    }
    vh0(index0) = 0;
  }
  
  return result;
}
