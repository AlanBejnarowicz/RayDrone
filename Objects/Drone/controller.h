#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <iostream>
#include <math.h>
#include <vector>

#include "MyVector.h"
#include "quaternion.h"
#include "InputSystem.h"


class PIDController{

    private:

        Tools::Vector3 MaxAngularSpeed = {10,10,10};


        // Rate controller
        Tools::Vector3 RateI;
        Tools::Vector3 RateLastError;


    public:

        PIDController();
        ~PIDController();

        float DtermAlpha = 0.2;

        //Rate PID values
        Tools::Vector3 Kp_Rate = {1,1,1};
        Tools::Vector3 Ki_Rate = {0.1,0.1,0.1};
        Tools::Vector3 Kd_Rate = {0.01, 0.01, 0.01};


        //methods

        Tools::Vector3 RatePID(Tools::GM_Inputs GMinput, Tools::Vector3 gyro, float dT);


};


#endif