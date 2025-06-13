#include "spring.hpp"
#include "pch.hpp"

namespace elem {


Spring1D::Spring1D() : id{0}, k{1.0} {
    ke << k, -k, -k, k;
}

Spring1D::Spring1D(int i, double iK) : id{i}, k{iK} {
    ke << k, -k, -k, k;
}

Spring1D::Spring1D(double iK) : id{0}, k{iK} {

    ke << k, -k, -k, k;

    
}

void Spring1D::print() const {

    std::cout << "Spring Constant, k:\n" << k << std::endl;
    std::cout << "Stiffness Matrix, ke:\n" << ke << std::endl;

    std::cout << "Nodal Displacements, u:\nu1:\n" << nodes[0].u << "\nu2:\n" << nodes[1].u << std::endl;
    std::cout << std::endl;
};

Spring2D::Spring2D() {}

Spring2D::Spring2D(double iK) : k{iK} {

    stiffMatrix << iK, -iK, -iK, iK;

    
}

void Spring2D::print() {

    std::cout << "Spring Constant, k:\n" << k << std::endl;
    std::cout << "Stiffness Matrix, ke:\n" << stiffMatrix << std::endl;
    
};
}