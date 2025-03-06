#include "motors.h"


Motors::Motors(){

}

Motors::~Motors(){


}


void Motors::UpdateMotors(Tools::GM_Inputs input){

/*

    Used Motor arangement

        1 --- 2
           #
        3 --- 4

*/
   


    // apply mixer
    Q4Mixer(input.pitch, input.roll, input.yaw, input.throttle);

    // simulate motors with alpha-beta filter
    for(int i = 0; i <4; i++){
        motors[i] = (motors[i] * alpha) + ((1 - alpha) * lastMotorsState[i]); 
        lastMotorsState[i] = motors[i];
    }

    // calculate thrust
    vertical_thrust = (motors[0] + motors[1] + motors[2] + motors[3]) * motorThrust;

    // calculate momentums
    momentums.x = (motors[3] + motors[4]) - (motors[1] + motors[2]); // pitch
    momentums.y = (motors[1] + motors[4]) - (motors[3] + motors[2]); // yaw
    momentums.z = (motors[1] + motors[3]) - (motors[4] + motors[2]); // roll

    momentums = momentums * ThrustToTorque;

}


void Motors::Q4Mixer (float pitch, float roll, float yaw, float throttle){

    motors[0] = throttle - pitch - roll + yaw;
    motors[1] = throttle - pitch + roll - yaw;
    motors[2] = throttle + pitch - roll - yaw;
    motors[3] = throttle + pitch + roll + yaw;

}