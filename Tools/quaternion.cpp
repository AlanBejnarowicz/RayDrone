#include "quaternion.h"

namespace Tools {



    // ############################################################
    // ##################   QUATERNION   ##########################




    Quaternion::Quaternion(double x, double y, double z, double w){
        this->w = w;
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Quaternion::Quaternion(void)
    {
        this->w = 1;
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
        double mag = magnitude();  // Use existing function
        if (mag > 1e-10) {  // Small threshold to prevent division by zero
            return Quaternion(x / mag, y / mag, z / mag, w / mag);
        }
        return Quaternion(0, 0, 0, 1);
    }



    // Conjugate
    Quaternion Quaternion::conjugate() const {
        return Quaternion(-x, -y, -z, w);
    }

    // Inverse
    Quaternion Quaternion::inverse() const {

        double mag = magnitude();
        if (mag < 1e-10) {  // Prevent division by zero
            return Quaternion(0, 0, 0, 1);  // Return identity quaternion
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
        os << "(" << q.x << "i, " << q.y << "j, " << q.z << "k, " << q.w << "w )";
        return os;
    }




    // ########################################  MATH  ########################################


    //Quaternion derivative

    Quaternion Quaternion::derivative(const Vector3 omegaB) const {
        Quaternion omega(omegaB.x, omegaB.y, omegaB.z, 0);
        return (omega * (*this)) * 0.5; 
    }

    // Quaternion multiplication
    Quaternion Quaternion::operator*(const Quaternion& q) const {
        return Quaternion(
            w * q.x + x * q.w + y * q.z - z * q.y, // x component
            w * q.y - x * q.z + y * q.w + z * q.x, // y component
            w * q.z + x * q.y - y * q.x + z * q.w, // z component
            w * q.w - x * q.x - y * q.y - z * q.z  // w component
        );
    }

    // Scalar multiplication
    Quaternion Quaternion::operator*(float scalar) const {
        return Quaternion(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    Quaternion Quaternion::operator+(const Quaternion& q) const {
        return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
    }

    Quaternion Quaternion::operator-(const Quaternion& q) const {
        return Quaternion(x - q.x, y - q.y, z - q.z, w - q.w);
    }


    // Scalar division
    Quaternion Quaternion::operator/(float scalar) const {
        return Quaternion(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    // Equality check
    bool Quaternion::operator==(const Quaternion& q) const {
        const double epsilon = 1e-6;  // Small threshold to compare floating points
        return (fabs(w - q.w) < epsilon) &&
               (fabs(x - q.x) < epsilon) &&
               (fabs(y - q.y) < epsilon) &&
               (fabs(z - q.z) < epsilon);
    }




}