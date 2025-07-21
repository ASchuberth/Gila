#include <bitset>
#include <cmath>

enum IsotropicElasticConstantFlags {
  lambda_defined,
  mu_defined,
  E_defined,
  nu_defined,
  K_defined,
  num_flags,
};

/// @brief Contains all 5 of the isotropic elastic constants
/**
 * Only 2 need to be defined as the other 3 can be determined
 * from the other 2.
 */
class IsotropicElasticConstant {

public:
  std::bitset<IsotropicElasticConstantFlags::num_flags> flags;

  /// @brief Lame's constant, \f$\lambda\f$
  double lambda;
  /// @brief Shear modulus/Lame's constant, \f$\mu\f$ or \f$G\f$
  double mu;
  /// @brief Modulus of elasticity, \f$E\f$
  double E;
  /// @brief Poisson's ratio, \f$\nu\f$
  double nu;
  /// @brief Bulk modulus, \f$K\f$
  double K;
};

/// @brief Claculate \f$\lambda\f$ from the shear modulus, \f$\mu\f$, and
/// modulus of
///        elasticity, \f$E\f$
/// @param mu Shear modulus of material, \f$\mu\f$
/// @param E Modulus of elasticity of material, \f$E\f$
/// @return Lame's Constant, \f$\lambda\f$
double calcLambda_mu_E(double mu, double E) {

  return (mu * (E - 2 * mu)) / (3 * mu - E);
}

double calcLambda_mu_nu(double mu, double nu) {

  return (2 * mu * nu) / (1 - 2 * nu);
}

double calcLambda_mu_K(double mu, double K) { return (K - (2 / 3) * mu); }

double calcLambda_E_nu(double E, double nu) {

  return (nu * E) / ((1 + nu) * (1 - 2 * nu));
}

double calcLambda_E_K(double E, double K) {

  return (3 * (K * E - 3 * std::pow(K, 2))) / (E - 9 * K);
}