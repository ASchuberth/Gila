#pragma once
#include <iostream>

namespace node {

class Node1D {

public:
    
    Node1D() : u{0.0} {}

    Node1D(double x) : u{x}{}

    void print() {
        std::cout << "u:\n" << u << std::endl;
    }

    double u;

private:


};

}