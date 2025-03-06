#include "InputSystem.h"

namespace Tools {


    InputSystem::InputSystem(){

            // SDL Gamecontroller
        if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0) {
            std::cerr << "Failed to initialize SDL: " << std::endl;
        }


        if (SDL_NumJoysticks() > 0) {
            Vgamepad = SDL_GameControllerOpen(0);
            std::cout << "Gamepad " << ": " << SDL_GameControllerName(Vgamepad) << std::endl;
        }

        // zero input
        gm_inputs = {0,0,0,0,0,0};

    }


    InputSystem::~InputSystem(){

    }

    GM_Inputs* InputSystem::GetGM_Inputs_ptr(void){
        return &gm_inputs;
    }



    // Handle Inputs
    void InputSystem::HandleGamepadInput(){

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

        gm_inputs.throttle = leftTrigger;
        gm_inputs.yaw = rightStickX;
        gm_inputs.pitch = leftStickY;
        gm_inputs.roll = leftStickX;

        // std::cout << "Throttle: " << gm_inputs.throttle << std::endl;
        // std::cout << "Yaw: " << gm_inputs.yaw << std::endl;
        // std::cout << "Pitch: " << gm_inputs.pitch << std::endl;
        // std::cout << "Roll: " << gm_inputs.roll << std::endl;
 

    }




}