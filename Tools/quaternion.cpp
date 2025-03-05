#include "quaternion.h"

namespace Tools {

    Quaternion::Quaternion(double w, double x, double y, double z){
        this->w = w;
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Quaternion::Quaternion(void)
    {
        this->w = 0;
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }

    Quaternion::~Quaternion()
    {
    }



    // Magnitude
    double Quaternion::magnitude() const {
        return std::sqrt(w * w + x * x + y * y + z * z);
    }


    // Normalization
    Quaternion Quaternion::normalize() const {
        double m = magnitude();
        return Quaternion(w / m, x / m, y / m, z / m);
    }



    // Conjugate
    Quaternion Quaternion::conjugate() const {
        return Quaternion(w, -x, -y, -z);
    }

    // Inverse
    Quaternion Quaternion::inverse() const {
        return conjugate() / (magnitude() * magnitude());
    }




    // ########################################  FRIENDS  ########################################
    // Print function for Quaternion
    std::ostream& operator<<(std::ostream& os, const Quaternion& q) {
        os << "(" << q.w << ", " << q.x << "i, " << q.y << "j, " << q.z << "k)";
        return os;
    }




    // ########################################  MATH  ########################################

    // Quaternion multiplication
    Quaternion Quaternion::operator*(const Quaternion& q) const {
        return Quaternion(
            w * q.w - x * q.x - y * q.y - z * q.z,
            w * q.x + x * q.w + y * q.z - z * q.y,
            w * q.y - x * q.z + y * q.w + z * q.x,
            w * q.z + x * q.y - y * q.x + z * q.w
        );
    }

    // Scalar multiplication
    Quaternion Quaternion::operator*(float scalar) const {
        return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
    }

    Quaternion Quaternion::operator+(const Quaternion& q) const {
        return Quaternion(w + q.w, x + q.x, y + q.y, z + q.z);
    }

    Quaternion Quaternion::operator-(const Quaternion& q) const {
        return Quaternion(w - q.w, x - q.x, y - q.y, z - q.z);
    }


    // Scalar division
    Quaternion Quaternion::operator/(float scalar) const {
        return Quaternion(w / scalar, x / scalar, y / scalar, z / scalar);
    }

    // Equality check
    bool Quaternion::operator==(const Quaternion& q) const {
        return w == q.w && x == q.x && y == q.y && z == q.z;
    }


}