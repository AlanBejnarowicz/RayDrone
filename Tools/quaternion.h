
#ifndef QUATERNION_H
#define QUATERNION_H

#include <iostream>
#include <math.h>

#include <raylib.h>

#include "MyVector.h"

namespace Tools {

class Vector3;

class Quaternion {

    private:
        /* data */
    public:
        double x, y, z, w;

        // constructors
        Quaternion(double x, double y, double z, double w);
        Quaternion(); // default constructor

        ~Quaternion();

        
        // functions
        double magnitude() const;
        Quaternion normalize() const;
        Quaternion conjugate() const;
        Quaternion inverse() const;
        Matrix RotationMatrix() const;


        // quaternion derivative
        Quaternion derivative(const Vector3 omegaB) const;


        // raylib quaternion compatibility
        // Convert between Tools::Vector3 and Raylib::Quaternion
        Quaternion(const ::Quaternion& v); // Convert from Raylib Quaternion
        operator ::Quaternion() const;  // Convert to Raylib Quaternion


        // casting on Tools::Vector3
        operator ::Tools::Vector3() const;  // Convert to Tools::Vector3


        // overrides

        //sum
        Quaternion operator+(const Quaternion& q) const;
        Quaternion operator-(const Quaternion& q) const;

        // scalar and quaternion multiplication
        Quaternion operator*(const Quaternion& q) const;
        Quaternion operator*(float scalar) const;

        Quaternion operator/(float scalar) const;
        bool operator==(const Quaternion& q) const;

        // #####   friends   #####
        friend std::ostream& operator<<(std::ostream& os, const Quaternion& q);

        // Friend function for scalar multiplication
        friend Quaternion operator*(float scalar, const Quaternion& q);


    };

}

#endif // QUATERNION_H
