#include "spring.hpp"
#include "pch.hpp"

namespace elem {


Spring1D::Spring1D() : k{1.0} {
    ke << k, -k, -k, k;
}



Spring1D::Spring1D(double iK) : k{iK} {

    ke << k, -k, -k, k;

    
}

void Spring1D::print() const {

    std::cout << "Spring Constant, k:\n" << k << std::endl;
    std::cout << "Stiffness Matrix, ke:\n" << ke << std::endl;

    std::cout << "Nodal Displacements, u:\nu1:\n" << displacements(0) << "\nu2:\n" << displacements(1) << std::endl;
    std::cout << "Forces, f:\n" << forces << std::endl;
    std::cout << std::endl;


};

}