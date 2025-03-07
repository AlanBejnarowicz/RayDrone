
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
        velocity = {0,0,0};
        
        //precompute diagonal inverse inertia
        //!!!! DIAG ELEMENTS CANNOT BE ZERO !!!!
    
        invInertiaDiag.x = 1 / InertiaDiag.x;
        invInertiaDiag.y = 1 / InertiaDiag.y;
        invInertiaDiag.z = 1 / InertiaDiag.z;

        //!!!! DIAG ELEMENTS CANNOT BE ZERO !!!!

        // init IMU
        virtualIMU.last_rotation = rotation;
        

        // load mesh for drone
        droneMesh = GenMeshCube(1.0f, 0.25f, 1.0f);






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



void Quadcopter::DrawDrone3D (Tools::Vector3 pos, Tools::Quaternion rotation, Tools::Vector3 size, Wireframe3D *wireframe) {
    // Apply rotation and move it to position
    Matrix transform = MatrixMultiply(rotation.RotationMatrix(), MatrixTranslate(pos.x, pos.y, pos.z));
    
    // Draw the cube mesh with red color
    Material material = LoadMaterialDefault();
    material.maps[MATERIAL_MAP_DIFFUSE].color = RED;
    DrawMesh(droneMesh, material, transform);


}







// GameObject methods
void Quadcopter::Update(float dt) {
    apply_deadband();

    Tools::Vector3 localOmega = virtualIMU.SimulateGyro(rotation, dt);

    std::cout << "Local Omega: " << localOmega << std::endl;

    Tools::Vector3 PID_out = PID.RatePID(gm_input_deadband, localOmega, dt);

    std::cout << "PID_out: " << PID_out << std::endl;

    //gm_input_deadband.pitch = PID_out.x;
    gm_input_deadband.yaw = PID_out.x;
    //gm_input_deadband.roll = PID_out.z;

    std::cout<<"yaw: " << gm_input_deadband.roll << std::endl;

    Q4Motors.UpdateMotors(gm_input_deadband);

    UpdateDronePhysics(dt);

    if(position.y <= 0){
        position.y = 0;
        velocity.y = 0;
    }


}





void Quadcopter::Draw() {

    Vector3 r_pos = {position.x, position.y, position.z};
    //DrawCubeWires(r_pos, 1.0, 0.2, 1.0 , GREEN);

    Tools::Vector3 size = {1,1,1};
    DrawDrone3D(position,rotation,size,&droneModel);

}



void Quadcopter::Draw2D() {
   

}