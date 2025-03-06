
#ifndef VGAMEPAD_H
#define VGAMEPAD_H

#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>


#include "../../Tools/MyVector.h"
#include "../GameObject.h"


class VGamepad : public GameObject {

    private:

    float VGM_square_size = 0.15;
    float VGM_square_Y_pos = 0.8;
    float VGM_box_separation = 0.05;

    Color fillColor = {5,5,5, 80};
    Color extColor = {0,0,0,255};
    Color dotColor = {255,0,0,200};


    Tools::Vector3 axis_1;
    Tools::Vector3 axis_2;

    public:

    //int gamepad = 1; // which gamepad to display
    SDL_GameController* Vgamepad = nullptr;


    VGamepad(); // default constructor
    VGamepad(SDL_GameController* gmpd); // default constructor
    ~VGamepad();

    void Update(float dt) override;
    void Draw() override;
    void Draw2D() override;
    


};


#endif