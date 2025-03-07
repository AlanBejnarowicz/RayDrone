#ifndef vIMU_H
#define vIMU_H


#include <iostream>
#include <math.h>
#include <vector>

#include "MyVector.h"
#include "quaternion.h"

class vIMU {

    private:
    


    public:
    Tools::Quaternion last_rotation;

    vIMU(); 
    vIMU(Tools::Quaternion initial_rotation); 
    ~vIMU();


    // methods
    Tools::Vector3 SimulateGyro(Tools::Quaternion rotation, float dT);

};


#endif