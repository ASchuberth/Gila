#include "render/render.hpp"

namespace GILA_APP_NAMESPACE {

class Gila {

public:
  /// @brief
  void run();

  /// @brief
  void mainLoop();

  void runImgui();

protected:
private:
  GilaRender mRender;
};

} // namespace GILA_APP_NAMESPACE