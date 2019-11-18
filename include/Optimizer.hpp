#ifndef __CCGO_OPTIMIZER_HPP__
#define __CCGO_OPTIMIZER_HPP__
#include "TargetFunction.hpp"
#include "Constraint.hpp"

namespace ccgo {
  typedef double (*BetaWT)(const Eigen::VectorXd&, const Eigen::VectorXd&, const Eigen::VectorXd&);
  enum STEP_WT {FLETCHER_REEVES, POLAK_RIBIERE, HESTENES_STIEFEL, DAI_YUAN};
  class Optimizer {
  public:
    Optimizer();
    virtual ~Optimizer();
    long getN() const;
    long getNTotal() const;
    const Eigen::VectorXd& getInitialParameters(const std::string&) const noexcept(false);
    const Eigen::VectorXd& getFinalParameters(const std::string&) const noexcept(false);
    void addTarget(TargetFunction*) noexcept(false);
    void addConstraint(Constraint*) noexcept(false);
    void addTargetToConstraint(const std::string&, const std::string&) noexcept(false);
    void setParameters(const std::string&, const Eigen::VectorXd&) noexcept(false);
    void enableConstraint(const std::string&) noexcept(false);
    void disableConstraint(const std::string&) noexcept(false);
    void enableTarget(const std::string&) noexcept(false);
    void disableTarget(const std::string&) noexcept(false);
    void setFinalParameters(const Eigen::VectorXd&);
    int optimize();
  private:
    double f(const Eigen::VectorXd&) const;
    Eigen::VectorXd df(const Eigen::VectorXd&) const;
    Eigen::MatrixXd d2f(const Eigen::VectorXd&) const;
    void incLambdaIndexes(const long&);
    void decLambdaIndexes(const long&);
    void decLambdaIndexesByOne(const long&);
    Eigen::VectorXd getInitialParamVector() const;
    int lsearch(const Eigen::VectorXd&, const Eigen::VectorXd&, double*) const;
    void onFitBegin(const Eigen::VectorXd&);
    void onFitEnd(const Eigen::VectorXd&);
    long _n;
    long _nTotal;
    int _nIter;
    int _nIterLS;
    double _tol;
    double _tolLS;
    double (*beta)(const Eigen::VectorXd&, const Eigen::VectorXd&, const Eigen::VectorXd&);
    static double beta_FLETCHER_REEVES(const Eigen::VectorXd&, const Eigen::VectorXd&, const Eigen::VectorXd&);
    static double beta_POLAK_RIBIERE(const Eigen::VectorXd&, const Eigen::VectorXd&, const Eigen::VectorXd&);
    static double beta_HESTENES_STIEFEL(const Eigen::VectorXd&, const Eigen::VectorXd&, const Eigen::VectorXd&);
    static double beta_DAI_YUAN(const Eigen::VectorXd&, const Eigen::VectorXd&, const Eigen::VectorXd&);
    static BetaWT betaByName(const STEP_WT&);
    std::unordered_map<std::string, TargetFunction*> _targets;
    std::unordered_map<std::string, Constraint*> _constraints;
  };
}

#endif
