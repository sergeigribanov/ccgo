#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__
#include <iostream>
#include <Eigen/Dense>

void vcout(const Eigen::VectorXd& x);

void mcout(const Eigen::MatrixXd& m);

#endif
