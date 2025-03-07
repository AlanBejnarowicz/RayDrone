
#include "quadcopter.h"


Quadcopter::Quadcopter()// Initialize gamepad to 0 or the desired index
{
    Start();

}

Quadcopter::Quadcopter(Tools::GM_Inputs* gmpd)// Initialize gamepad to 0 or the desired index
{
    gm_input = gmpd;
    Start();
}

Quadcopter::~Quadcopter()
{

}



void Quadcopter::Start(void){

        // ensure zero start conditions
        position = {0,0,0};
        last_possition = position;
        rotation = {1,0,0,0};
        last_rotation = rotation;
        velocity = {0,0,0};
        
        //precompute diagonal inverse inertia
        //!!!! DIAG ELEMENTS CANNOT BE ZERO !!!!
    
        invInertiaDiag.x = 1 / InertiaDiag.x;
        invInertiaDiag.y = 1 / InertiaDiag.y;
        invInertiaDiag.z = 1 / InertiaDiag.z;

        //!!!! DIAG ELEMENTS CANNOT BE ZERO !!!!


}


// apply deadband to inputs preventing noise
void Quadcopter::apply_deadband(){

    // copy values from gm_input to local variable gm_input_deadband
    if (gm_input != nullptr) {
        gm_input_deadband.throttle = gm_input->throttle;
        gm_input_deadband.yaw = gm_input->yaw;
        gm_input_deadband.roll = gm_input->roll;
        gm_input_deadband.pitch = gm_input->pitch;

        // apply deadband
        if(abs(gm_input_deadband.throttle) <= JoystickDeadband)
            gm_input_deadband.throttle = 0;

        if(abs(gm_input_deadband.yaw) <= JoystickDeadband)
            gm_input_deadband.yaw = 0;

        if(abs(gm_input_deadband.roll) <= JoystickDeadband)
            gm_input_deadband.roll = 0;

        if(abs(gm_input_deadband.pitch) <= JoystickDeadband)
            gm_input_deadband.pitch = 0;
    } else {
        std::cout << "Gamepad is nullptr !!!" << std::endl;
    }
}


void Quadcopter::UpdateDronePhysics(float dT){

    Tools::Vector3 FG = gravity * mass;

    //std::cout << "Thrust: "<< Q4Motors.vertical_thrust << std::endl; 

    Tools::Vector3 thrustBody = {0 ,Q4Motors.vertical_thrust ,0 };
    //std::cout << "Thrust: "<< thrustBody << std::endl;

    // calculate thrust in local coordinates
    
    Tools::Vector3 thrustGlobal = thrustBody * rotation;
    //std::cout << "Thrust Global: "<< thrustGlobal << std::endl;

    Tools::Vector3 totalF = FG + thrustGlobal;
    Tools::Vector3 acceleration = totalF / mass;

    // integrate acceleration velocity to possition
    velocity = velocity + acceleration * dT;
    position = position + velocity * dT;


    // Rotation
    Tools::Vector3 omegaBody = angularMomentumBody * invInertiaDiag;

    //cross produvt of omegaBody and angularMomentumBody
    Tools::Vector3 crossTerm = omegaBody ^ angularMomentumBody;

    Tools::Vector3 dLdT = Q4Motors.momentums - crossTerm;

    // integrate angular momentum
    angularMomentumBody = angularMomentumBody + dLdT * dT;

    // update omega body
    omegaBody = angularMomentumBody * invInertiaDiag;

    Tools::Quaternion qDot = rotation.derivative(omegaBody);

    //integrate rotation
    rotation = rotation + (qDot * dT);
    rotation = rotation.normalize();

}


// GameObject methods
void Quadcopter::Update(float dt) {
    apply_deadband();
    Q4Motors.UpdateMotors(gm_input_deadband);

    UpdateDronePhysics(dt);

    if(position.y <= 0){
        position.y = 0;
        velocity.y = 0;
    }

    


}

void Quadcopter::Draw() {

    Vector3 r_pos = {position.x, position.y, position.z};
    DrawCubeWires(r_pos, 1.0, 0.2, 1.0 , GREEN);

}



void Quadcopter::Draw2D() {
   

}