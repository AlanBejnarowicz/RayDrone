#include "controller.h"




PIDController::PIDController(){


}


PIDController::~PIDController(){


}



Tools::Vector3 PIDController::RatePID(Tools::GM_Inputs GMinput, Tools::Vector3 gyro, float dT){

        Tools::Vector3 input = {-GMinput.pitch, GMinput.yaw, GMinput.roll};

        // aplly max angular speeds
        input = input * MaxAngularSpeed;

        //calculate error
        Tools::Vector3 error = input - gyro;

        // calculate Integral term
        RateI = RateI + ((error * Ki_Rate) * dT);

        // D term with alphaBeta Lowpass filter
        Tools::Vector3 errorDerivative = (error - RateLastError) / dT;
        RateLastError = error;

        // lowpass
        //RateD = (errorDerivative * DtermAlpha) + (RateD * (1 - DtermAlpha));
        RateD = RateD * Kd_Rate;

        
        // anti wind-up
        if (RateI.x > MaxIntegral) RateI.x = MaxIntegral;
        if (RateI.x < -MaxIntegral) RateI.x = -MaxIntegral;
        if (RateI.y > MaxIntegral) RateI.y = MaxIntegral;
        if (RateI.y < -MaxIntegral) RateI.y = -MaxIntegral;
        if (RateI.z > MaxIntegral) RateI.z = MaxIntegral;
        if (RateI.z < -MaxIntegral) RateI.z = -MaxIntegral;


        // zero integral when throttle is low
        if(GMinput.throttle < 0.2){
            RateI = {0,0,0};
        }

        Tools::Vector3 omega = (error * Kp_Rate) + RateI + RateD;

        return omega;

}