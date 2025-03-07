#include "quaternion.h"

namespace Tools {



    // ############################################################
    // ##################   QUATERNION   ##########################




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


    //Quaternion derivative

    Quaternion Quaternion::derivative(const Vector3 omegaB) const {
        Quaternion q_dot;
        q_dot.w = 0.5 * (-x * omegaB.x - y * omegaB.y - z * omegaB.z);
        q_dot.x = 0.5 * (w * omegaB.x + y * omegaB.z - z * omegaB.y);
        q_dot.y = 0.5 * (w * omegaB.y - x * omegaB.z + z * omegaB.x);
        q_dot.z = 0.5 * (w * omegaB.z + x * omegaB.y - y * omegaB.x);
        return q_dot;

    }

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