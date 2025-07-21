
#include "elements/assembly.hpp"
#include "gila.hpp"
#include "observer/subject.hpp"
#include "render/render.hpp"


VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE

void run(GILA_APP_NAMESPACE::GilaRender &render) {}

void runImgui(Model *model) {}

/**
 *  Spring Constant         - k
 *  Spring Stiffness Matrix - ke
 *  Global Stiffness Matrix - K
 *
 *
 *  1D - One Dimensional, i.e.   (x),       (x0)
 *  2D - Two Dimensional, i.e.   (x, y),    (x0, x1)
 *  3D - Three Dimensional, i.e. (x, y, z), (x0, x1, x2)
 */

int main() {

  // Example 1
  // elem::Spring1D s1{50.0f};
  // elem::Spring1D s2{75.0f};

  // assy::Assembly1D assembly;

  // assembly.addElement(s1);
  // assembly.addElement(s2);

  // assembly.assemble();

  // assembly.addForce(1, 75.0);
  // assembly.addForce(2, 75.0);

  // assembly.displacementConstraint(0, 0.0);

  GILA_APP_NAMESPACE::Gila GilaApp;

  try {
    GilaApp.run();
  } catch (vk::SystemError &err) {
    std::cout << "vk::SystemError: " << err.what() << std::endl;
    exit(-1);
  } catch (std::exception &err) {
    std::cout << "std::exception: " << err.what() << std::endl;
    exit(-1);
  } catch (...) {
    std::cout << "unknown error\n";
    exit(-1);
  }

  // Example 2

  const double W = 10.0;
  const double k = 1.0;
  elem::Spring1D s1{3.0 * k};
  elem::Spring1D s2{2.0 * k};
  elem::Spring1D s3{1.0 * k};

  assy::Assembly1D assembly;

  assembly.addElement(s1);
  assembly.addElement(s2);
  assembly.addElement(s3);

  assembly.assemble();

  assembly.addForce(1, W);
  assembly.addForce(2, W);
  assembly.addForce(3, W);

  assembly.displacementConstraint(0, 0.0);

  try {

    assembly.solve();

  } catch (const std::exception &err) {
    std::cerr << err.what() << std::endl;
    return -1;
  }

  assembly.print();

  return 0;
}