
#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <math.h>


#include "quaternion.h"

namespace Tools {

    class Vector3 {

        private:
            /* data */
        public:
            double x, y, z;

            // constructors
            Vector3(double x, double y, double z);
            Vector3(); // default constructor

            ~Vector3();

            
            // functions
            double magnitude() const;
            Vector3 normalize() const;


            // overrides

            //sum
            Vector3 operator+(const Vector3& q) const;
            Vector3 operator-(const Vector3& q) const;

            // Vector3 element-wise multiplication
            Vector3 operator*(const Vector3& v) const;

            //scaling
            Vector3 operator*(float scalar) const;

            // Rotate Vector by Quaternion
            Vector3 operator*(const Quaternion& q) const;


            Vector3 operator/(float scalar) const;
            bool operator==(const Vector3& q) const;

            // #####   friends   #####
            friend std::ostream& operator<<(std::ostream& os, const Vector3& q);



    };


}


#endif // VECTOR_H
