#ifndef GWORLD_H
#define GWORLD_H

#include "raylib.h"
#include "rlgl.h"       // Required to define vertex data (immediate-mode style)

#include <iostream>
#include <math.h>
#include <random>
#include <vector>


#include "MyVector.h"
#include "GameObject.h"

class GameWorld : public GameObject{

    private:
    Texture2D def_texture;

    std::vector<Vector3> box_map; 


    public:

    GameWorld();
    ~GameWorld();


    void Update(float dt) override;
    void Draw() override;
    void Draw2D() override;


};



#endif