#include <iostream>
#include "TargetChiSquare.hpp"
#include "TestConstraint.hpp"
#include "Optimizer.hpp"

int main(int argc, char* argv[]) {
  ccgo::TargetChiSquare q("q", 3);
  ccgo::TestConstraint tc("tc", 5.);
  ccgo::Optimizer opt;
  opt.addTarget(&q);
  opt.addConstraint(&tc);
  opt.enableTarget("q");
  opt.enableConstraint("tc");
  // tc.add(&q);
  // q.setBeginIndex(0);
  // Eigen::VectorXd x0(3);
  // x0(0) = 1;
  // x0(1) = 2;
  // x0(2) = 3;
  // q.setInitialParameters(x0);
  // Eigen::MatrixXd im(3, 3);
  // im(0, 0) = 1;
  // im(1, 1) = 1;
  // im(2, 2) = 1;
  // q.setInverseErrorMatrix(im);
  // Eigen::VectorXd x(3);
  // std::cout << q.f(x) << std::endl;
  return 0;
}
