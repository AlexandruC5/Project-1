#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL_gamecontroller.h"

#define MAX_KEYS 300
#define MAX_BUTTONS 100

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

enum BUTTON_STATE
{
	BUTTON_IDLE = 0,
	BUTTON_DOWN,
	BUTTON_REPEAT,
	BUTTON_UP,
	};

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();
	bool gamepad2_on = false;

public:
	KEY_STATE keyboard[MAX_KEYS];
	BUTTON_STATE button[MAX_BUTTONS];


	KEY_STATE controller_A_button;
	KEY_STATE controller_Y_button;
	KEY_STATE controller_X_button;
	KEY_STATE controller_B_button;
	KEY_STATE controller_START_button;
	KEY_STATE controller_Dpad_LEFT;
	KEY_STATE controller_Dpad_RIGHT;
	KEY_STATE controller_Dpad_UP;
	KEY_STATE controller_Dpad_DOWN;
	KEY_STATE joystick_UP;
	KEY_STATE joystick_DOWN;
	KEY_STATE joystick_LEFT;
	KEY_STATE joystick_RIGHT;
	

	KEY_STATE controller2_A_button;
	KEY_STATE controller2_Y_button;
	KEY_STATE controller2_X_button;
	KEY_STATE controller2_B_button;
	KEY_STATE controller2_START_button;
	KEY_STATE controller2_Dpad_LEFT;
	KEY_STATE controller2_Dpad_RIGHT;
	KEY_STATE joystick2_UP;
	KEY_STATE joystick2_DOWN;
	KEY_STATE joystick2_LEFT;
	KEY_STATE joystick2_RIGHT;

	SDL_GameController * gamepad;
	SDL_GameController * gamepad2;
};

#endif // __ModuleInput_H__