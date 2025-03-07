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



    // Convert from Raylib's Quaternion
    Quaternion::Quaternion(const ::Quaternion& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

    // Convert to Raylib's Quaternion
    Quaternion::operator ::Quaternion() const {
        return { x, y, z, w };
    }


    //convert to Tools::Vector3 
    Quaternion::operator ::Tools::Vector3() const {
        return { x, y, z };
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
        double mag = magnitude();
        if (mag == 0) {
            throw std::runtime_error("Cannot invert a quaternion with zero magnitude");
        }
        return conjugate() / (mag * mag);
    }

    // Inverse
    Matrix Quaternion::RotationMatrix() const {
        Matrix r;

        r.m0 = 1 - 2 * (y * y + z * z);
        r.m1 = 2 * (x * y - z * w);
        r.m2 = 2 * (x * z + y * w);
        r.m3 = 0;

        r.m4 = 2 * (x * y + z * w);
        r.m5 = 1 - 2 * (x * x + z * z);
        r.m6 = 2 * (y * z - x * w);
        r.m7 = 0;

        r.m8 = 2 * (x * z - y * w);
        r.m9 = 2 * (y * z + x * w);
        r.m10 = 1 - 2 * (x * x + y * y);
        r.m11 = 0;

        r.m12 = 0;
        r.m13 = 0;
        r.m14 = 0;
        r.m15 = 1;

        return r;
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