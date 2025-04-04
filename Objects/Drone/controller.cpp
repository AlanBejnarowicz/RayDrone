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













//////////////////////////////////////
// QUATERNIONS
//////////////////////////////////////


QuaternionController::QuaternionController(){


}


QuaternionController::~QuaternionController(){


}


Tools::Vector3 QuaternionController::QControllerUpdate(Tools::Quaternion q_ref, Tools::Quaternion rotation, Tools::Vector3 omega, float dT){

    // 1. Calculate error quaternion q_err = q_ref * conj(q_meas)
    Tools::Quaternion q_err = q_ref * rotation.conjugate();
    q_err = q_err.normalize();

    // 2. Convert to axis-angle
    Tools::AxisAngle q_axag;
    q_axag = q_err.ToAxisAngle();
    Tools::Vector3 axis = q_axag.axis;

    std::cout << "Axis: " << axis << "   Angle: " << q_axag.angle << std::endl;

    // // 3. Proportional torque: -Kp * angle * axis
    // //    negative sign => if angle>0, we want to push back
    // Tools::Vector3 axis = q_axag.axis;
    // Tools::Vector3 tau_p = axis * (-Kp * q_axag.angle);

    // // 4. Derivative torque for rate damping: -Kd * omega_meas
    // Tools:: Vector3 tau_d = omega * (-Kd);

    // // net torque
    // Tools::Vector3 tau = tau_p + tau_d;


    Tools::Vector3 tau;

    return tau;


}
