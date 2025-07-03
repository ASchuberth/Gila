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

    double lambda;
    double mu;
    double E;
    double nu;
    double K;


};

double calcLambda_mu_E(double mu, double E) {
    
    return (mu * (E - 2 * mu)) / (3*mu - E);

}

double calcLambda_mu_nu(double mu, double nu) {
    
    return (2 * mu * nu) / (1 - 2 * nu);

}

double calcLambda_mu_K(double mu, double K) {
    
    return (K - (2/3) * mu);

}

double calcLambda_E_nu(double E, double nu) {

    return (nu * E) / ((1 + nu) * (1 - 2 * nu));

}

double calcLambda_E_K(double E, double K) {

    return (3 * (K * E - 3 * std::pow(K,2))) / (E - 9*K);

}