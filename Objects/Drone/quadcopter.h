
#ifndef TCLASS_H
#define TCLASS_H

#include <iostream>
#include <math.h>

#include "InputSystem.h"

#include "MyVector.h"
#include "quaternion.h"
#include "GameObject.h"


//  drone classes
#include "motors.h"


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
    void UpdateDronePhysics(float dt);


    public:
    Motors Q4Motors;

    Tools::Vector3 velocity;


    Tools::Quaternion last_rotation;
    Tools::Vector3 last_possition;



    Quadcopter(); // default constructor
    Quadcopter(Tools::GM_Inputs* gmpd);
    
    ~Quadcopter();

    void Update(float dt) override;
    void Draw() override;
    void Draw2D() override;

};


#endif