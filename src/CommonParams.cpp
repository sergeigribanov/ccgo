#include "CommonParams.hpp"

ccgo::CommonParams::CommonParams(const std::string& name, const long& n)
    : ccgo::ParamContainer(n), _name(name) {}

ccgo::CommonParams::~CommonParams() {}

std::string ccgo::CommonParams::getName() const { return _name; }
