#pragma once
#include "node.hpp"

namespace elem {


class Spring1D {
    public:
    Spring1D();

    Spring1D(int i, double iK);

    Spring1D(double iK);


    void print() const;

    node::Node1D nodes[2] = {0.0, 0.0};

    int id;

private:

    /** \brief Spring constant of element */
    double k;

    /** \brief Spring element stiffness matrix */
    Eigen::Matrix2d ke;

};

class Spring2D {

public:
    Spring2D();

    Spring2D(double iK);


    void print();

private:

    /** \brief Spring constant of element */
    double k;

    /** \brief Spring element stiffness matrix */
    Eigen::Matrix2d stiffMatrix;


};
}