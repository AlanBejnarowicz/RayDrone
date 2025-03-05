
#ifndef QUATERNION_H
#define QUATERNION_H

#include <iostream>
#include <math.h>

namespace Tools {

    class Quaternion {

    private:
        /* data */
    public:
        double x, y, z, w;

        // constructors
        Quaternion(double w, double x, double y, double z);
        Quaternion(); // default constructor

        ~Quaternion();

        
        // functions
        double magnitude() const;
        Quaternion normalize() const;
        Quaternion conjugate() const;
        Quaternion inverse() const;



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
