#include "Switch.hpp"

ccgo::Switch::Switch() : _enabled(false) {}

ccgo::Switch::~Switch() {}

bool ccgo::Switch::isEnabled() const { return _enabled; }

void ccgo::Switch::enable() { _enabled = true; }

void ccgo::Switch::disable() { _enabled = false; }
