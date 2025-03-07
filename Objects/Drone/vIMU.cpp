#include "vIMU.h"

vIMU::vIMU(){

}


vIMU::vIMU(Tools::Quaternion initial_rotation){

    // take initial value
    last_rotation = initial_rotation;

}

vIMU::~vIMU(){

}


Tools::Vector3 vIMU::SimulateGyro(Tools::Quaternion rotation, float dT){

    // calculating difference between Quaternions
    Tools::Quaternion qDelta = rotation * last_rotation.inverse();

    // std::cout << "qDelta: "<< qDelta <<std::endl; 

    last_rotation = rotation;

    // extract w and v
    float w = qDelta.w;
    Tools::Vector3 v = qDelta;

    float epsilon = 1e-8f;
    float cosHalfAngle = std::max(-1.0f, std::min(w, 1.0f));

    float angle = 2.0f * (float)acos(cosHalfAngle);
    // 4) If angle is very small, use small-angle approximation for axis
    float sinHalfAngle = (float)sqrt(1.0f - cosHalfAngle*cosHalfAngle);


    Tools::Vector3 axis;
    if (abs(sinHalfAngle) > epsilon)
    {
        axis = v / sinHalfAngle; // normalizing
    }
    else
    {
        // Fallback: if angle~0, use v directly or default axis
        // (the direction won't matter if angle is tiny)
        axis = {1.0f, 0, 0}; // arbitrary
    }

    // 5) Angular velocity = (angle / dt) * axis
    //    in the same coordinate frame that qDelta represents
    float rate = angle / dT;
    Tools::Vector3 omega = axis * rate;

     // Convert to drone's local frame
    Tools::Vector3 localOmega = omega * rotation;
    
    // convert to (roll pitch yaw)  from (pitch, yaw, roll)
    Tools::Vector3 RPYlocalOmega = {localOmega.z, localOmega.x, localOmega.y};


    return RPYlocalOmega;
}


