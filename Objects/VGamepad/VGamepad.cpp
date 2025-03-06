
#include "VGamepad.h"



VGamepad::VGamepad()// Initialize gamepad to 0 or the desired index
{

}

VGamepad::VGamepad(SDL_GameController* gmpd) // Initialize gamepad to 0 or the desired index
{
    Vgamepad = gmpd;
}

VGamepad::~VGamepad()
{

}

// GameObject methods
void VGamepad::Update(float dt) {


    SDL_PumpEvents();  // Update SDL's internal state

    float leftStickX = SDL_GameControllerGetAxis(Vgamepad, SDL_CONTROLLER_AXIS_LEFTX) / 32767.0f;
    float leftStickY = SDL_GameControllerGetAxis(Vgamepad, SDL_CONTROLLER_AXIS_LEFTY) / 32767.0f;
    float rightStickX = SDL_GameControllerGetAxis(Vgamepad, SDL_CONTROLLER_AXIS_RIGHTX) / 32767.0f;
    float rightStickY = SDL_GameControllerGetAxis(Vgamepad, SDL_CONTROLLER_AXIS_RIGHTY) / 32767.0f;
    float leftTrigger = SDL_GameControllerGetAxis(Vgamepad, SDL_CONTROLLER_AXIS_TRIGGERLEFT) / 32767.0f;
    float rightTrigger = SDL_GameControllerGetAxis(Vgamepad, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) / 32767.0f;
    

    // std::cout << "Left Stick X: " << leftStickX << std::endl;
    // std::cout << "Left Stick Y: " << leftStickY << std::endl;
    // std::cout << "Right Stick X: " << rightStickX << std::endl;
    // std::cout << "Right Stick Y: " << rightStickY << std::endl;
    // std::cout << "Left Trigger: " << leftTrigger << std::endl;
    // std::cout << "Right Trigger: " << rightTrigger << std::endl;


    axis_1.x = leftStickX;
    axis_1.y = -leftStickY;
    axis_2.x = rightStickX;
    axis_2.y = -(leftTrigger * 2 - 1);
    


}

void VGamepad::Draw() {
    

}

void VGamepad::Draw2D() {
    // to optimise

    int screen_w = GetScreenWidth();
    int screen_h = GetScreenHeight();

    float s = (screen_h * VGM_square_size);

    float box_x = (screen_w / 2);
    float box_y = (screen_h * VGM_square_Y_pos);

    float separation = (s * VGM_box_separation);

    Rectangle r1 = {box_x + separation, box_y, s, s};
    Rectangle r2 = {box_x - s - separation, box_y, s, s};

    Vector2 c1 = {r1.x + (r1.width/2), r1.y + (r1.height/2)};
    Vector2 c2 = {r2.x + (r2.width/2), r2.y + (r2.height/2)};

    // to optimise, can be run only one window resized


    DrawRectangleRounded(r1, 0.1f, 10, fillColor);
    DrawRectangleRounded(r2, 0.1f, 10, fillColor);

    DrawRectangleRoundedLinesEx(r1, 0.1f, 10, 2.0, extColor);
    DrawRectangleRoundedLinesEx(r2, 0.1f, 10, 2.0, extColor);

    
    Tools::Vector3 c1_ax1(r1.x + (r1.width/2), r1.y + (r1.height/2), 0);
    Tools::Vector3 c2_ax2(r2.x + (r2.width/2), r2.y + (r2.height/2),0);

    c1_ax1 = c1_ax1 + (axis_1 * s / 2);
    c2_ax2 = c2_ax2 + (axis_2 * s / 2);

    Vector2 v1 = {c1_ax1.x, c1_ax1.y};
    Vector2 v2 = {c2_ax2.x, c2_ax2.y};

    DrawCircleV(v1, 5, dotColor);
    DrawCircleV(v2, 5, dotColor);

    //const char* gamepadText = TextFormat("GP%d: %s", gamepad, GetGamepadName(gamepad));
    //int textWidth = MeasureText(gamepadText, 20);
    //DrawText(gamepadText, box_x - (textWidth / 2), box_y + s + separation, 20, BLACK);



}