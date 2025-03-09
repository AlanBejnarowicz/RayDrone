#include "raylib.h"
#include "raymath.h"
#include "rcamera.h"
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

//change coordinate system




int main() {
    
    // Camera and window initialization

    const int screenWidth = 1600;
    const int screenHeight = 1000;
    
    InitWindow(screenWidth, screenHeight, "RayDroneSim");

    Camera3D camera = { 0 };
    camera.position = { 0.0f, 5.0f, -10.0f }; // Like Unity (Camera starts behind)
    camera.target = { 0.0f, 2.0f, 0.0f };   // Looking towards +Z
    camera.up = { 0.0f, 1.0f, 0.0f };       // Keep Y-up (same as Unity)
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    //CameraMode(camera, CAMERA_FREE); // Allows movement without fixed target


    SetTargetFPS(120);


    // ############### GAMEPAD FIX ############### 

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
        
        //set camera to possition of drone, as FPV camera
        // Assuming the first game object is the drone
        if (!gameObjects.empty()) {
            Quadcopter* drone = dynamic_cast<Quadcopter*>(gameObjects[1].get());
            if (drone) {
                Vector3 dronePosition = drone->position;
                Tools::Quaternion droneRotation = drone->rotation;

                // Set camera position to drone's position
                camera.position = dronePosition;

                // Forward direction for FPV camera is negative Z
                Tools::Vector3 v = {0,0,1};
                Tools::Vector3 camforward = v * droneRotation.inverse();
                // Update camera target
                camera.target = Vector3Add(camera.position, camforward);

                // up vector (positive Y) rotated by drone quaternion
                Tools::Vector3 up = Tools::Vector3(0, 1, 0) * droneRotation.inverse();
                camera.up = up;  // <-- This line enables roll rotation
            }
        }

        // Update
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

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




    //SDL_GameControllerClose(gamepad);

    CloseWindow(); // Close window and OpenGL context
    return 0;
}
