#include "APlugin.hh"

bool APlugin::runSet() {
  return true;
}

bool APlugin::runGet() {
  return false;
}

bool APlugin::run() {
  _get = new std::thread(&APlugin::runGet, this);
  _set = new std::thread(&APlugin::runSet, this);
  return true;
}
