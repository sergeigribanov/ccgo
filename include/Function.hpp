/*
 * CCGO optimizer
 * See COPYRIGHT file at the top of the source tree.
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
 * @file Function.hpp
 *
 * @brief Function class definition
 *
 * @ingroup ccgo
 *
 * @author Sergei Gribanov
 * Contact: ssgribanov@gmail.com
 *
 */

#ifndef __CCGO_FUNCTION_HPP__
#define __CCGO_FUNCTION_HPP__

#include <Eigen/Dense>
#include <string>
#include <unordered_map>

#include "CommonParams.hpp"

namespace ccgo {
/**
 * Implementation of a facility that provide abstract methods,
 * that introduced in order to get a value, a gradient or a
 * hessian of a some function
 */
class Function {
 public:
  //! A constructor
  Function();
  //! A destructor
  virtual ~Function();
  /*!
   * This method returns a function value
   *
   * @param x (vector of parameters)
   *
   */
  virtual double f(const Eigen::VectorXd& x) const = 0;
  /*!
   * This method returns a function gradient
   *
   * @param x (vector of parameters)
   *
   */
  virtual Eigen::VectorXd df(const Eigen::VectorXd& x) const = 0;
  /*!
   * This method returns a function hessian
   *
   * @param x (vector of parameters)
   *
   */
  virtual Eigen::MatrixXd d2f(const Eigen::VectorXd& x) const = 0;
  /*!
   * This method assigns an unordered map of common parameter pointers.
   * Key value of a map is a name of a common parameter container.
   *
   * @param params (unordered map of common parameter pointers)
   *
   */
  void setCommonParameters(std::unordered_map<std::string, CommonParams*>*);
  /*!
   * This method assigns an unordered map of constants.
   * Key value of a map is a name of a constant.
   *
   * @param constants (unordered map of pointers to constants)
   *
   */
  void setConstants(std::unordered_map<std::string, double>*);

 protected:
  /*!
   * This method returns pointer to unordered map of common parameter pointers
   */
  std::unordered_map<std::string, CommonParams*>* getCommonParameters() const;
  /*!
   * This method returns pointer to unordered map of constants
   */
  std::unordered_map<std::string, double>* getConstants() const;

 private:
  /*!
   * Unordered map of common parameter pointers
   */
  std::unordered_map<std::string, CommonParams*>* _commonParams;
  /*!
   * Unordered map of constant pointers
   */
  std::unordered_map<std::string, double>* _constants;
};
}  // namespace ccgo

#endif
