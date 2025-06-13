#pragma once
#include <iostream>
#include <vector>
#include <map>

#include "spring.hpp"

namespace assy {

    class Assembly1D {

    public:

        Assembly1D() : elemId{0} {}


        int elemId;
        std::vector<node::Node1D> nodes;
        std::map<int, elem::Spring1D> elements;

        void addElement(const elem::Spring1D& spring) {
            elements[elemId] = spring;

            elemId += 1;
        }

        void print() {

            for (const auto& elem : elements) {
                std::cout << "Elemenet Id:  " << elem.first << "\n";
                elem.second.print();
            }
        }

    };

}