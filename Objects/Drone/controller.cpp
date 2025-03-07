#include "controller.h"




PIDController::PIDController(){


}


PIDController::~PIDController(){


}



Tools::Vector3 PIDController::RatePID(Tools::GM_Inputs GMinput, Tools::Vector3 gyro, float dT){

        Tools::Vector3 input = {GMinput.yaw, GMinput.pitch, GMinput.roll};

        // aplly max angular speeds
        input = input * MaxAngularSpeed;

        //calculate error
        Tools::Vector3 error = input - gyro;

        // calculate Integral term
        RateI = RateI + ((error * Ki_Rate) * dT);

        // D term with alphaBeta Lowpass filter
        Tools::Vector3 RateD = ( (error * DtermAlpha) - RateLastError * (1 - DtermAlpha)) / dT ;

        RateD = RateD * Kd_Rate;
   


        // anti wind-up
        if(RateI.x > 0.2f)
            RateI.x = 0.2f;

        if(RateI.x > 0.2f)
            RateI.x = 0.2f;

        if(RateI.x > 0.2f)
            RateI.x = 0.2f;


        // zero integral when throttle is low
        if(GMinput.throttle < 0.2){
            RateI = {0,0,0};
        }

        Tools::Vector3 omega = (error * Kp_Rate) + RateI + RateD;

        return omega;

}