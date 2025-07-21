#include "observer.hpp"
#include "pch.hpp"

namespace GILA_APP_NAMESPACE {

Observer::Observer() {}

Observer::~Observer() {}

void Observer::onNotify(int id, const RenderData &renderables) {
  std::cout << renderables << std::endl;
}

} // namespace GILA_APP_NAMESPACE