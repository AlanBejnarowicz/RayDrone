#include "raylib.h"
#include "raymath.h"
#include "rcamera.h"

#include <SDL2/SDL.h>
#include <omp.h>      


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
#include "Objects/World/Gworld.h"
#include "MainCamera/main_camera.h"


// main collection of GameObjects
std::vector<std::unique_ptr<GameObject>> gameObjects;




int main() {
    
    // Camera and window initialization

    const int screenWidth = 2000;
    const int screenHeight = 1200;

    SetConfigFlags(FLAG_MSAA_4X_HINT);      // Enable Multi Sampling Anti Aliasing 4x (if available)

    
    InitWindow(screenWidth, screenHeight, "RayDroneSim");

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
    //gameObjects.push_back(std::make_unique<GameWorld>());

    MainCamera mainCamera(gameObjects[1].get());


    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Handle SDL input for gamepad
        Input_System.HandleGamepadInput();

        // Parallel update
        #pragma omp parallel for
        for (int i = 0; i < static_cast<int>(gameObjects.size()); i++) {
            gameObjects[i]->Update(dt);
        }

        mainCamera.Update(dt);
        

        // Draw
        BeginDrawing();


        ClearBackground(RAYWHITE);
        BeginMode3D(mainCamera.camera);


        DrawGrid(500, 0.25f);

        for (auto& obj : gameObjects) {
            obj->Draw();
        }


        EndMode3D();


        for (auto& obj : gameObjects) {
            obj->Draw2D();
        }

        mainCamera.Draw2D();

        DrawText("RayDroneSim V0.02", 10, 10, 20, DARKGRAY);
        EndDrawing();


    }




    //SDL_GameControllerClose(gamepad);

    CloseWindow(); // Close window and OpenGL context
    return 0;
}
