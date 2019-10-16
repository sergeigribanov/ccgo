#include "debug.hpp"

void vcout(const Eigen::VectorXd& x) {
  std::cout << x << std::endl;
}

void mcout(const Eigen::MatrixXd& m) {
  std::cout << m << std::endl;
}
