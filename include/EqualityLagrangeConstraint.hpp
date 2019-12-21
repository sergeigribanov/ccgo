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
 * @file EqualityLagrangeConstraint.hpp
 *
 * @brief EqualityLagrangeConstraint class definition
 *
 * @ingroup ccgo
 *
 * @author Sergei Gribanov
 * Contact: ssgribanov@gmail.com
 *
 */

#ifndef __CCGO_EQUALITY_LAGRANGE_CONSTRAINT_HPP__
#define __CCGO_EQUALITY_LAGRANGE_CONSTRAINT_HPP__

#include "LagrangeConstraint.hpp"

namespace ccgo {
/**
 * Implementation of equality Lagrange constraint facility
 */
class EqualityLagrangeConstraint : public LagrangeConstraint {
 public:
  //! A constructor
  /*!
   * @param name (constraint name)
   */
  explicit EqualityLagrangeConstraint(const std::string&);
  //! A destructor
  virtual ~EqualityLagrangeConstraint();
  virtual double f(const Eigen::VectorXd&) const override final;
  virtual Eigen::VectorXd df(const Eigen::VectorXd&) const override final;
  virtual Eigen::MatrixXd d2f(const Eigen::VectorXd&) const override final;
};
}  // namespace ccgo

#endif
