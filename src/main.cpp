#include <iostream>
#include "TargetChiSquare.hpp"
#include "TestConstraint.hpp"
#include "Optimizer.hpp"

int main(int argc, char* argv[]) {
  ccgo::TargetChiSquare q("q", 2);
  ccgo::TestConstraint tc("tc", 2.);
  ccgo::Optimizer opt;
  opt.addTarget(&q);
  opt.addConstraint(&tc);
  Eigen::VectorXd x0(2);
  x0(0) = 1;
  x0(1) = 1;
  q.setInitialParameters(x0);
  opt.enableTarget("q");
  opt.enableConstraint("tc");
  opt.addTargetToConstraint("q", "tc");
  Eigen::MatrixXd im(2, 2);
  im(0, 0) = 1;
  im(1, 1) = 1;
  q.setInverseErrorMatrix(im);
  opt.optimize();
  Eigen::VectorXd xf = q.getFinalParameters();
  std::cout << "Final parameters:" << std::endl;
  std::cout << xf << std::endl;
  return 0;
}
