#include <Eigen/Dense>
#include <iostream>
#include <map>
#include <vector>

namespace elem {

class Spar1D {

public:
  /// @brief Default Constructor
  Spar1D() {};

  /// @brief Constructor with spring constant provided
  /// @param iK Spring constant - Units: Force / Length
  Spar1D(double iK) {};

  /// @brief Prints out element info to console
  void print() const;

  /// @brief Spar stiffness matrix
  Eigen::Matrix2d ke;

  /// @brief Displacements of spring nodes
  Eigen::Vector2d displacements;

  /// @brief Forces acting upon element
  Eigen::Vector2d forces;

private:
  /// \brief Young's Modulus of Element
  double E;

  /// @brief Cross-Sectional Area of Spar
  double A;

  /// @brief Length of Spar
  double l;
};
} // namespace elem