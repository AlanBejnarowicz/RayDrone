
#ifndef TCLASS_H
#define TCLASS_H

#include <iostream>
#include <math.h>
#include <vector>

#include <raylib.h>
#include "raymath.h"

#include "InputSystem.h"

#include "MyVector.h"
#include "quaternion.h"
#include "GameObject.h"


//  drone classes
#include "motors.h"
#include "vIMU.h"
#include "controller.h"

struct WireframePoint{    
    Tools::Vector3 point;
    std::vector<int> neighbours;
};

struct Wireframe3D{
    Tools::Vector3 origin = {0,0,0};
    std::vector <WireframePoint> elements;
    Color wire_color = GREEN;
};



class Quadcopter : public GameObject {


    private:

    Tools::Vector3 InertiaDiag = {0.084,0.084,0.168};
    Tools::Vector3 invInertiaDiag;
    Tools::Vector3 angularMomentumBody;
    float mass = 1.0;


    Tools::Vector3 gravity = {0, -9.81, 0};
    float CX_coef = 0.01;

    float JoystickDeadband = 0.05;
    Tools::GM_Inputs* gm_input = nullptr;
    Tools::GM_Inputs gm_input_deadband;

    
    // private functions
    void Start(void);
    void apply_deadband(void);
    void UpdateDronePhysics(float dT);
    void DrawDrone3D (Tools::Vector3 pos, Tools::Quaternion rotation, Tools::Vector3 size, Wireframe3D *wireframe);


    //3D model
    Wireframe3D droneModel;
    Mesh droneMesh;

    // Define a quaternion for rotation (-Yaw for left-handed system)
    Tools::Quaternion UnityCoordinate = QuaternionFromEuler(0.0f, -PI / 4.0f, 0.0f);



    public:
    Motors Q4Motors;
    vIMU virtualIMU;
    PIDController PID;

    Tools::Vector3 velocity;
    Tools::Vector3 last_possition;



    Quadcopter(); // default constructor
    Quadcopter(Tools::GM_Inputs* gmpd);
    
    ~Quadcopter();

    void Update(float dt) override;
    void Draw() override;
    void Draw2D() override;

};


#endif