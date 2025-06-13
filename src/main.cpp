
#include "elements/assembly.hpp"


int main() {


    elem::Spring1D s1{50.0f};
    elem::Spring1D s2{75.0f};

    assy::Assembly1D assembly;

    
    double force = 1.0;

    Eigen::Vector2d forces(2);
    forces(0) = 0.0;
    forces(1) = force;

    std::cout << "Forces:\n" << forces << std::endl << std::endl;

    assembly.addElement(s1);
    assembly.addElement(s2);

    assembly.print();

   

    return 0;
}