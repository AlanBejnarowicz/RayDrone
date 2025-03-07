#include "MyVector.h"

namespace Tools {

    Vector3::Vector3( double x, double y, double z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3::Vector3(void)
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }

    Vector3::~Vector3()
    {
    }
    


    // Convert from Raylib's Vector3
    Vector3::Vector3(const ::Vector3& v) : x(v.x), y(v.y), z(v.z) {}

    // Convert to Raylib's Vector3
    Vector3::operator ::Vector3() const {
        return { x, y, z };
    }




    // Magnitude
    double Vector3::magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }


    // Normalization
    Vector3 Vector3::normalize() const {
        double m = magnitude();
        return Vector3(x / m, y / m, z / m);
    }



    // ########################################  FRIENDS  ########################################
    // Print function for Vector3
    std::ostream& operator<<(std::ostream& os, const Vector3& q) {
        os << "(" << q.x << "i, " << q.y << "j, " << q.z << "k)";
        return os;
    }



    // ########################################  MATH  ########################################

    // Vector3 element-wise multiplication
    Vector3 Vector3::operator*(const Vector3& v) const {
        return Vector3(
            x * v.x, 
            y * v.y,
            z * v.z
        );
    }

    // Scalar multiplication
    Vector3 Vector3::operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    Vector3 Vector3::operator+(const Vector3& q) const {
        return Vector3(x + q.x, y + q.y, z + q.z);
    }

    Vector3 Vector3::operator-(const Vector3& q) const {
        return Vector3(x - q.x, y - q.y, z - q.z);
    }


    // Scalar division
    Vector3 Vector3::operator/(float scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    // Equality check
    bool Vector3::operator==(const Vector3& q) const {
        return x == q.x && y == q.y && z == q.z;
    }


    // Vector Quaterinon multiplication
    Vector3 Vector3::operator*(const Quaternion& q) const{
        Quaternion v_quat(0, x, y, z);
        Quaternion result = q * v_quat * q.conjugate();
        return Vector3(result.x, result.y, result.z);
    }


       // Scalar multiplication
       Vector3 Vector3::operator^(const Vector3& q) const {
        return Vector3(
            y * q.z - z * q.y,
            z * q.x - x * q.z,
            x * q.y - y * q.x
        );
    }






}