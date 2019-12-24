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
 * @file ParamContainer.cpp
 *
 * @brief Implementation of ParamContainer methods
 *
 * @ingroup ccgo
 *
 * @author Sergei Gribanov
 * Contact: ssgribanov@gmail.com
 *
 */

#include "ParamContainer.hpp"

ccgo::ParamContainer::ParamContainer(long n)
    : _xInitial(Eigen::VectorXd::Zero(n)), _xFinal(Eigen::VectorXd::Zero(n)) {}

ccgo::ParamContainer::~ParamContainer() {}

long ccgo::ParamContainer::getBeginIndex() const { return _beginIndex; }

long ccgo::ParamContainer::getN() const { return _xInitial.size(); }

long ccgo::ParamContainer::getNFixed() const { return _fixedParams.size(); }

const Eigen::VectorXd& ccgo::ParamContainer::getInitialParameters() const {
  return _xInitial;
}

const Eigen::VectorXd& ccgo::ParamContainer::getFinalParameters() const {
  return _xFinal;
}

void ccgo::ParamContainer::setInitialParameters(const Eigen::VectorXd& x) {
  if (x.size() == _xInitial.size()) {
    _xInitial = x;
    _xFinal = x;
  } else {
    // TODO: exception
  }
}

void ccgo::ParamContainer::setBeginIndex(long index) { _beginIndex = index; }

void ccgo::ParamContainer::setFinalParameters(const Eigen::VectorXd& xfull) {
  _xFinal = xfull.segment(getBeginIndex(), getN());
}

void ccgo::ParamContainer::setPeriod(long index, double left, double right) {
  if (right <= left) {
    // TO DO: exception
  }
  if (index < _xInitial.size() && index >= 0) {
    _periodical.push_back(std::make_pair(index, std::make_pair(left, right)));
  } else {
    // TO DO: exception
  }
}

void ccgo::ParamContainer::checkPeriodical(Eigen::VectorXd* x) const {
  long index;
  int nsteps;
  double period;
  for (const auto& el : _periodical) {
    if (isFixedParameter(el.first)) {
      continue;
    }
    index = _beginIndex + el.first;
    if ((*x)[index] >= el.second.second) {
      period = el.second.second - el.second.first;
      nsteps = ((*x)[index] - el.second.second) / period + 1;
      (*x)[index] -= nsteps * period;
    } else if ((*x)[index] < el.second.first) {
      period = el.second.second - el.second.first;
      nsteps = (el.second.first - (*x)[index]) / period + 1;
      (*x)[index] += nsteps * period;
    }
  }
}

bool ccgo::ParamContainer::havePeriodical() const {
  return _periodical.size() > 0;
}

bool ccgo::ParamContainer::isFixedParameter(long index) const {
  return (_fixedParams.find(index) != _fixedParams.end());
}

void ccgo::ParamContainer::fixParameter(long index) {
  if (index >= 0 && index < getN()) {
    _fixedParams.insert(index);
  } else {
    // TO DO : exception
  }
}

void ccgo::ParamContainer::releaseParameter(long index) {
  auto it = _fixedParams.find(index);
  if (it != _fixedParams.end()) {
    _fixedParams.erase(it);
  }
}

const std::set<long>& ccgo::ParamContainer::getFixedParamIndices() const {
  return _fixedParams;
}
