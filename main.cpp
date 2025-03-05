#include "raylib.h"

#include <iostream>


// include tools
#include "Tools/quaternion.h"
#include "Tools/MyVector.h"

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "RayLib 3D Game Example");
    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; 
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);


    // quaternion test

    Tools::Quaternion q1(1, 2, 3, 4);
    Tools::Quaternion q2(4 ,3 ,2 ,1);

    std::cout << q1 + q2 << std::endl;


    Tools::Vector3 v1(1, 2, 3);
    Tools::Vector3 v2(4, 5, 6);
    Tools::Quaternion q(0.7071f, 0, 0.7071f, 0); // 90-degree rotation around Y-axis


    std::cout <<std::endl << "********* Rotation Test ********* " << std::endl;
    std::cout << "Vector 1 before: " << v1 << std::endl;

    v1 = v1 * q;


    std::cout << "Vector 1 after: " << v1 << std::endl;


    while (!WindowShouldClose()) {
        // Update
        UpdateCamera(&camera, CAMERA_ORBITAL);
        
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        DrawGrid(10, 1.0f);
        EndMode3D();
        DrawText("3D RayLib Scene", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context
    return 0;
}
