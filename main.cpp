#include "raylib.h"
#include <SDL2/SDL.h>


#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>
#include <vector>
#include <memory>
#include <iostream>


// include tools
#include "Tools/quaternion.h"
#include "Tools/MyVector.h"
#include "Tools/InputSystem.h"



// include Objects
#include "Objects/GameObject.h"
#include "Objects/VGamepad/VGamepad.h"
#include "Objects/Drone/quadcopter.h"

// main collection of GameObjects
std::vector<std::unique_ptr<GameObject>> gameObjects;


int main() {
    
    // Camera and window initialization

    const int screenWidth = 1600;
    const int screenHeight = 1000;
    
    InitWindow(screenWidth, screenHeight, "RayDroneSim");
    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; 
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(120);


    // ############### GAMEPAD FIX ############### 

    // SDL Gamecontroller
    if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0) {
        std::cerr << "Failed to initialize SDL: " << std::endl;
        return -1;
    }



    SDL_GameController* gamepad = nullptr;
    if (SDL_NumJoysticks() > 0) {
        gamepad = SDL_GameControllerOpen(0);
        std::cout << "Gamepad " << ": " << SDL_GameControllerName(gamepad) << std::endl;

    }

    Tools::InputSystem Input_System;

    // Get pointer to GMInputs
    Tools::GM_Inputs* GMInputs = Input_System.GetGM_Inputs_ptr();


    // ############### END GAMEPAD FIX ###############




    // #########################
    //  $$$$$ Init Objects $$$$$


    gameObjects.push_back(std::make_unique<VGamepad>(GMInputs));
    gameObjects.push_back(std::make_unique<Quadcopter>(GMInputs));


    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Handle SDL input for gamepad
        Input_System.HandleGamepadInput();

        // Update objects
        for (auto& obj : gameObjects) {
            obj->Update(dt);
        }
        

        // Update
        UpdateCamera(&camera, CAMERA_ORBITAL);
        // Draw
        BeginDrawing();


        ClearBackground(RAYWHITE);
        BeginMode3D(camera);


        DrawGrid(100, 1.0f);

        for (auto& obj : gameObjects) {
            obj->Draw();
        }


        EndMode3D();


        for (auto& obj : gameObjects) {
            obj->Draw2D();
        }


        DrawText("RayDroneSim V0.01", 10, 10, 20, DARKGRAY);
        EndDrawing();


    }




    SDL_GameControllerClose(gamepad);

    CloseWindow(); // Close window and OpenGL context
    return 0;
}
