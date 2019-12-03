#ifndef __CCGO_SWITCH_HPP__
#define __CCGO_SWITCH_HPP__

namespace ccgo {
  class Switch {
  public:
    Switch();
    virtual ~Switch();
    bool isEnabled() const;
    void enable();
    void disable();
  private:
    bool _enabled;
  };
}

#endif
