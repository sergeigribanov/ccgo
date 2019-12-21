# CCGO: Constrained Conjugate Gradient Optimizer

The CCGO has been designed for use in the KFBase kinematic fit package (https://github.com/sergeigribanov/KFBase).
At this moment the optimization method is pretty simple. To find the optimum of the function f(x) the equation grad(f) = 0
is solved using the Newton method.

## Installing

1. git clone https://github.com/sergeigribanov/ccgo.git
2. Create a directory to build the package in a suitable location and change the current directory to this one.
3. To build the package run the following commands:
    1. cmake -DCMAKE_INSTALL_PREFIX=\<CCGO installation prefix\> -DEIGEN3_INCLUDE_DIR=\<path to Eigen3 installation\> \<path to CCGO source code\>
    2. make
    3. make install
