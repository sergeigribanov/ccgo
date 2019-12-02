#include <iostream>
#include "TargetChiSquare.hpp"

ccgo::TargetChiSquare::TargetChiSquare(const std::string& name, const long& n):
  TargetFunction(name, n), _inverseErrorMatrix(Eigen::MatrixXd::Zero(n, n)) {
}

ccgo::TargetChiSquare::~TargetChiSquare() {
}

const Eigen::MatrixXd& ccgo::TargetChiSquare::getInverseErrorMatrix() const {
  return _inverseErrorMatrix;
}

double ccgo::TargetChiSquare::f(const Eigen::VectorXd& x) const {
  Eigen::VectorXd dx = x - getInitialParameters();
  return dx.transpose() * _inverseErrorMatrix * dx;
}

Eigen::VectorXd ccgo::TargetChiSquare::df(const Eigen::VectorXd& x) const {
  Eigen::VectorXd dx = x - getInitialParameters();
  return 2 * _inverseErrorMatrix * dx;
}

Eigen::MatrixXd ccgo::TargetChiSquare::d2f(const Eigen::VectorXd& x) const {
  Eigen::VectorXd dx = x - getInitialParameters();
  return 2 * _inverseErrorMatrix;
}

void ccgo::TargetChiSquare::setInverseErrorMatrix(const Eigen::MatrixXd& matrix) {
  if (matrix.rows() == matrix.cols() && matrix.rows() == getN()) {
    _inverseErrorMatrix = matrix;
  } else {
    std::cerr << "[ERROR] Wrong matrix size!" << std::endl;
    // TODO: exception
  }
}

void ccgo::TargetChiSquare::onFitBegin(const Eigen::VectorXd&) {
}

void ccgo::TargetChiSquare::onFitEnd(const Eigen::VectorXd&) {
}
