#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>

namespace Tools {

    struct GM_Inputs
    {
        float throttle;
        float yaw;
        float pitch;
        float roll;

        // buttons
        float bt_1;
        float bt_2;
    };

    class InputSystem {

        private:
        //int gamepad = 1; // which gamepad to display
        SDL_GameController* Vgamepad = nullptr;


        public:

        InputSystem(); // default constructor        
        ~InputSystem();

        void HandleGamepadInput();
        GM_Inputs* GetGM_Inputs_ptr(void);

        GM_Inputs gm_inputs;
        

    };



}


#endif