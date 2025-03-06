
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
        rotation = {0,0,0,0};
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


void Quadcopter::UpdateDronePhysics(float dt){

    Tools::Vector3 FG = gravity * mass;

}


// GameObject methods
void Quadcopter::Update(float dt) {
    apply_deadband();
    Q4Motors.UpdateMotors(gm_input_deadband);

    UpdateDronePhysics(dt);


}

void Quadcopter::Draw() {

    Vector3 r_pos = {position.x, position.y, position.z};
    DrawCubeWires(r_pos, 1.0, 0.2, 1.0 , GREEN);

}



void Quadcopter::Draw2D() {
   

}