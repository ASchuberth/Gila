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

class IsotropicElasticConstant {

public:
  std::bitset<IsotropicElasticConstantFlags::num_flags> flags;

  /// @brief Lame's constant, \f$\lambda\f$
  double lambda;
  /// @brief Shear modulus/Lame's constant, \f$\mu\f$ or G
  double mu;
  /// @brief Modulus of elasticity, E
  double E;
  /// @brief Poisson's ratio, \f$\nu\f$
  double nu;
  /// @brief Bulk modulus, K
  double K;
};

/// @brief Claculate \f$\lambda\f$ from the shear modulus, \f$\mu\f$, and
/// modulus of
///        elasticity, E
/// @param mu Shear modulus of material
/// @param E Modulus of elasticity of material
/// @return $\lambda$ constant
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