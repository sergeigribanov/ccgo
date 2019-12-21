# CCGO: Constrained Conjugate Gradient Optimizer

The CCGO has been designed for use in the KFBase kinematic fit package (https://github.com/sergeigribanov/KFBase).
At this moment the optimization method is pretty simple. To find the optimum of the function f(x) the equation grad(f) = 0
is solved using the Newton method.
