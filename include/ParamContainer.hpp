#ifndef __CCGO_PARAMCONTAINER_HPP__
#define __CCGO_PARAMCONTAINER_HPP__
#include <utility>
#include <set>
#include <vector>
#include <Eigen/Dense>

namespace ccgo {
  class ParamContainer {
  public:
    explicit ParamContainer(const long&);
    virtual ~ParamContainer();
    long getBeginIndex() const;
    long getN() const;
    long getNFixed() const;
    const std::set<long>& getFixedParamIndexes() const;
    bool havePeriodical() const;
    bool isFixedParameter(long) const;
    const Eigen::VectorXd& getInitialParameters() const;
    const Eigen::VectorXd& getFinalParameters() const;
    void setInitialParameters(const Eigen::VectorXd&);
    void setBeginIndex(const long&);
    void setFinalParameters(const Eigen::VectorXd&);
    void setPeriod(long, double, double);
    void checkPeriodical(Eigen::VectorXd*) const;
    void fixParameter(long);
    void releaseParameter(long);
  protected:
    Eigen::VectorXd _xInitial;
    Eigen::VectorXd _xFinal;
    std::vector<std::pair<long, std::pair<double, double>>> _periodical;
  private:
    long _beginIndex;
    std::set<long> _fixedParams;
  };
}

#endif
