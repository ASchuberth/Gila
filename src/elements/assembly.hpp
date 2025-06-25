#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <Eigen/Dense>

#include "spring.hpp"
#include "spar.hpp"

namespace assy {

    
    /// @brief 1D Assembly of spring elements and calculates their displacements
    /** Each spring element added gets assembled onto the previous with addElement().
     *  
     *  For Example:  
     *            Elem 1         Elem 2                    Elem n 
     *     _u0_/\  /\  /\_u1_/\  /\  /\_u2_ ..._un-1_/\  /\  /\_un           
     *           \/  \/        \/  \/                  \/  \/     
     * 
     *      The 2nd displacement of the previously added element is set to be equal to
     *      the 1st displacement of the element being added.
     *  
     */
    
    class Assembly1D {

    public:
        /// @brief Default Constructor
        Assembly1D() : numUnknowns{0},
                       globalStiffMatrixSize{0} 
                       {

                            displacements = Eigen::VectorXd::Zero(1);
                            forces = Eigen::VectorXd::Zero(1);
                            K = Eigen::MatrixXd::Zero(1,1);
        }

        
        /**
         * @brief Adds element to Assembly system
         * 
         * @param spring 1D Spring element (elem::Spring1D) with spring constant (k) defined
         */
        void addElement(const elem::Spring1D& spring) {
            elements.push_back(spring);
        }

        /**
         * @brief Prints out values of assembly
         * 
         */
        void print() const {

            int id = 0;
            for (const auto& elem : elements) {
                std::cout << "Element Id:  " << id << "\n";
                elem.print();
                id++;
            }

            std::cout << "Global Stiffness Matrix:\n" << K << std::endl;

            std::cout << "Displacements:\n" << displacements << std::endl;
            std::cout << "Forces:\n" << forces << std::endl;

            std::cout << "Number of Unknowns:\n" << numUnknowns << std::endl;

            std::cout << std::endl;
        }


        /// @brief Generates the global stiffness matrix, K
        /** K gets resized to a square matrix with a size equal to
         *  the number of elements in the assembly. 
         * 
         *  For each element in the assembly, the element's stiffness matrix
         *  gets summed to the 
         *  
         *  Example:
         *  
         *  For 2 Elements, Size of K = 3 X 3 matrix
         *  
         *  Elem 1: 
         *  K =
         *  [e1(0,0) e1(1,0) 0
         *   e1(0,1) e1(1,1) 0
         *    0       0      0]
         * 
         *  Elem 2: 
         *  K =
         *  [e1(0,0)       e1(1,0)          0 
         *   e1(0,1)  e1(1,1) + e2(0,0)  e2(1,0)
         *    0            e2(0,1)       e2(1,1)]
         * 
         */
        void assemble() {

            globalStiffMatrixSize = elements.size() + 1;

            numUnknowns = globalStiffMatrixSize * 2;

            K.resize(globalStiffMatrixSize, globalStiffMatrixSize);

            displacements.resize(globalStiffMatrixSize);
            forces.resize(globalStiffMatrixSize);

            // Zero resized vectors and matrices
            displacements = Eigen::VectorXd::Zero(globalStiffMatrixSize);
            forces = Eigen::VectorXd::Zero(globalStiffMatrixSize);
            K = Eigen::MatrixXd::Zero(globalStiffMatrixSize, globalStiffMatrixSize);


            displacements = Eigen::VectorXd::Constant(globalStiffMatrixSize, 0.0);
            forces = Eigen::VectorXd::Constant(globalStiffMatrixSize, 0.0);

            
            int i  = 0;
            for (const auto& e : elements) {

                K(i, i)         += e.ke(0, 0);
                K(i + 1, i)     += e.ke(1, 0);
                K(i, i + 1)     += e.ke(0,  1);
                K(i + 1, i + 1) += e.ke(1, 1);


                i++;
            }
        }

        /**
         * @brief Add displacement constraint to Assembly system
         * 
         * @param id The node id for the displacement constraint
         * @param value The value for the node displacement to equal
         */

        void displacementConstraint(int id, double value) {

            displacements(id) = value;

            numUnknowns--;
        }

        void addForce(int id, double value) {

            forces(id) = value;

            numUnknowns--;

        }

        void solveEachElementForces() {

            int i = 0;
            for (auto& elem : elements) {

                elem.displacements(0) = displacements(i);
                elem.displacements(1) = displacements(i+1);


                elem.forces = elem.ke * elem.displacements;

                i++;
            }
        }

        void solve() {

            if (numUnknowns != (int)(globalStiffMatrixSize)) {

                throw std::runtime_error("Error: System is over or under constrained!\n");

                return;
            }

            std::vector<int> rowsWithForceDefined;
            Eigen::MatrixXd KwForcedDefinedRowsOnly = K;
            int i = 0;
            for (const auto& force : forces) {
            
                if (force == 0) {
                    // Zero rows with undefined force
                    KwForcedDefinedRowsOnly({i}, Eigen::all) = 
                                            Eigen::MatrixXd::Zero(1, globalStiffMatrixSize);

                    // Zero the column as well, i.e. if zeroed row 2, then zero column 2
                    KwForcedDefinedRowsOnly(Eigen::all, {i}) = 
                                            Eigen::MatrixXd::Zero(globalStiffMatrixSize, 1);
                }

                i++;
                
            }
            

            displacements = KwForcedDefinedRowsOnly.colPivHouseholderQr().solve(forces);

            forces = K * displacements;
        
            solveEachElementForces();

        }

        
    private:

        /// @brief Vector to hold each element in assembly
        std::vector<elem::Spring1D> elements;

        /// @brief Global Stiffness MAtrix
        Eigen::MatrixXd K;

        /// @brief Displacements of System
        Eigen::VectorXd displacements;

        /// @brief Forces of System
        Eigen::VectorXd forces;

        /// @brief Number of Unkowns in System of Equations
        int numUnknowns;

        /// @brief Size of K, displacements, and forces
        size_t globalStiffMatrixSize;

    };

}