#pragma once



namespace elem {

/// @brief 1D Spring Element
/**
 *  
 * Individual spring element used in Assembly1D.
 * Defines the spring constant (k) and local stiffness matrix (ke) of a single element
 *  - k must be defined prior to adding to Assembly1D.
 *      - Currently, k can only be defined upon initialization (private member).
 * Assembly1D will solve the displacements and forces of each element.
 */
class Spring1D {
    public:

    /// @brief Default Constructor 
    Spring1D();

    /// @brief Constructor with spring constant provided
    /// @param iK Spring constant - Units: Force / Length
    Spring1D(double iK);

    /// @brief Prints out element info to console
    void print() const;

    
    /// @brief Spring stiffness matrix 
    Eigen::Matrix2d ke;
    
    /// @brief Displacements of spring nodes
    Eigen::Vector2d displacements;

    /// @brief Forces acting upon element
    Eigen::Vector2d forces;
    
private:

    /// \brief Spring constant of element 
    double k;

    
    

};

}