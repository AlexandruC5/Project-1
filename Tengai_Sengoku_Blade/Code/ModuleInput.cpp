#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput() : Module()
{
	for(uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;
}

// Destructor
ModuleInput::~ModuleInput()
{
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	SDL_Init(SDL_INIT_GAMECONTROLLER);

	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
	{
		LOG("SDL_GAMECONTROLLER could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if (SDL_NumJoysticks() > 0)
	{
		gamepad = SDL_GameControllerOpen(0);
		gamepad2 = SDL_GameControllerOpen(1);

		if (gamepad == NULL)
		{
			LOG("Warning! Unable to open GameController. SDL_Error: %s\n", SDL_GetError());
		}
		if (gamepad2 == NULL)
		{
			LOG("Warning! Unable to open GameController 2. SDL_Error: %s\n", SDL_GetError());
		}
	}
	

	
		
	

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_Event e;
	SDL_PollEvent(&e);

	if (e.type == SDL_QUIT)
		return update_status::UPDATE_STOP;


	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
			return update_status::UPDATE_STOP;
		else if (e.type == SDL_CONTROLLERDEVICEADDED) {
			if (!gamepad) {
				gamepad = SDL_GameControllerOpen(0);
				if (gamepad) {
					LOG("Controller loaded correctly");
				}
				else LOG("Could not open gamecontroller: %s", SDL_GetError());
			}
		}
		else if (e.type == SDL_CONTROLLERDEVICEREMOVED) {
			if (e.cdevice.which == 0) {
				SDL_GameControllerClose(gamepad);
				gamepad = nullptr;
				LOG("Controller removed!\n");
			}
		}
	}

	if (gamepad2){
		gamepad2_on = true;
	}
	//Controller 1
	Uint8 button_state_A = SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_A);
	Uint8 button_state_Y = SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_Y);
	Uint8 button_state_X = SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_X);
	Uint8 button_state_B = SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_B);
	Uint8 button_state_START = SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_START);
	Uint8 button_STATE_Dpad_LEFT = SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	Uint8 button_STATE_Dpad_RIGHT = SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	Uint8 button_STATE_Dpad_UP = SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_DPAD_UP);
	Uint8 button_STATE_Dpad_DOWN = SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
	Uint8 joystick_STATE_up = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTY) < -CONTROLLER_DEAD_ZONE;
	Uint8 joystick_STATE_down = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTY) > CONTROLLER_DEAD_ZONE;
	Uint8 joystick_STATE_right = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTX) > CONTROLLER_DEAD_ZONE;
	Uint8 joystick_STATE_left = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTX) < -CONTROLLER_DEAD_ZONE;

	if (button_state_A) {
		if (controller_A_button == KEY_IDLE) controller_A_button = KEY_DOWN;
		else controller_A_button = KEY_REPEAT;
	}
	else {
		if (controller_A_button == KEY_REPEAT || controller_A_button == KEY_DOWN) controller_A_button = KEY_UP;
		else controller_A_button = KEY_IDLE;
	}

	if (button_state_Y) {
		if (controller_Y_button == KEY_IDLE) controller_Y_button = KEY_DOWN;
		else controller_Y_button = KEY_REPEAT;
	}
	else {
		if (controller_Y_button == KEY_REPEAT || controller_Y_button == KEY_DOWN) controller_Y_button = KEY_UP;
		else controller_Y_button = KEY_IDLE;
	}
	if (button_state_X) {
		if (controller_X_button == KEY_IDLE) controller_X_button = KEY_DOWN;
		else controller_X_button = KEY_REPEAT;
	}
	else {
		if (controller_X_button == KEY_REPEAT || controller_X_button == KEY_DOWN) controller_X_button = KEY_UP;
		else controller_X_button = KEY_IDLE;
	}
	if (button_state_B) {
		if (controller_B_button == KEY_IDLE) controller_B_button = KEY_DOWN;
		else controller_B_button = KEY_REPEAT;
	}
	else {
		if (controller_B_button == KEY_REPEAT || controller_B_button == KEY_DOWN) controller_B_button = KEY_UP;
		else controller_B_button = KEY_IDLE;
	}

	if (button_state_START) {
		if (controller_START_button == KEY_IDLE) controller_START_button = KEY_DOWN;
		else controller_START_button = KEY_REPEAT;
	}
	else {
		if (controller_START_button == KEY_REPEAT || controller_START_button == KEY_DOWN) controller_START_button = KEY_UP;
		else controller_START_button = KEY_IDLE;
	}

	if (button_STATE_Dpad_LEFT) {
		if (controller_Dpad_LEFT == KEY_IDLE) controller_Dpad_LEFT = KEY_DOWN;
		else controller_Dpad_LEFT = KEY_REPEAT;
	}
	else {
		if (controller_Dpad_LEFT == KEY_REPEAT || controller_Dpad_LEFT == KEY_DOWN) controller_Dpad_LEFT = KEY_UP;
		else controller_Dpad_LEFT = KEY_IDLE;
	}
	if (button_STATE_Dpad_RIGHT) {
		if (controller_Dpad_RIGHT == KEY_IDLE) controller_Dpad_RIGHT = KEY_DOWN;
		else controller_Dpad_RIGHT = KEY_REPEAT;
	}
	else {
		if (controller_Dpad_RIGHT == KEY_REPEAT || controller_Dpad_RIGHT == KEY_DOWN) controller_Dpad_RIGHT = KEY_UP;
		else controller_Dpad_RIGHT = KEY_IDLE;
	}
	if (button_STATE_Dpad_UP) {
		if (controller_Dpad_UP == KEY_IDLE) controller_Dpad_UP = KEY_DOWN;
		else controller_Dpad_UP = KEY_REPEAT;
	}
	else {
		if (controller_Dpad_UP == KEY_REPEAT || controller_Dpad_UP == KEY_DOWN) controller_Dpad_UP = KEY_UP;
		else controller_Dpad_UP = KEY_IDLE;
	}
	if (button_STATE_Dpad_DOWN) {
		if (controller_Dpad_DOWN == KEY_IDLE) controller_Dpad_DOWN = KEY_DOWN;
		else controller_Dpad_DOWN = KEY_REPEAT;
	}
	else {
		if (controller_Dpad_DOWN == KEY_REPEAT || controller_Dpad_DOWN == KEY_DOWN) controller_Dpad_DOWN = KEY_UP;
		else controller_Dpad_DOWN = KEY_IDLE;
	}

	if (joystick_STATE_up) {
		if (joystick_UP == KEY_IDLE) joystick_UP = KEY_DOWN;
		else joystick_UP = KEY_REPEAT;
	}
	else {
		if (joystick_UP == KEY_REPEAT || joystick_UP == KEY_DOWN) controller_A_button = KEY_UP;
		else joystick_UP = KEY_IDLE;
	}
	if (joystick_STATE_down) {
		if (joystick_DOWN == KEY_IDLE) joystick_DOWN = KEY_DOWN;
		else joystick_DOWN = KEY_REPEAT;
	}
	else {
		if (joystick_DOWN == KEY_REPEAT || joystick_DOWN == KEY_DOWN) controller_A_button = KEY_UP;
		else joystick_DOWN = KEY_IDLE;
	}
	if (joystick_STATE_right) {
		if (joystick_RIGHT == KEY_IDLE) joystick_RIGHT = KEY_DOWN;
		else joystick_RIGHT = KEY_REPEAT;
	}
	else {
		if (joystick_RIGHT == KEY_REPEAT || joystick_RIGHT == KEY_DOWN) controller_A_button = KEY_UP;
		else joystick_RIGHT = KEY_IDLE;
	}

	if (joystick_STATE_left) {
		if (joystick_LEFT == KEY_IDLE) joystick_LEFT = KEY_DOWN;
		else joystick_LEFT = KEY_REPEAT;
	}
	else {
		if (joystick_LEFT == KEY_REPEAT || joystick_LEFT == KEY_DOWN) controller_A_button = KEY_UP;
		else joystick_LEFT = KEY_IDLE;
	}




	//Controller 2
	Uint8 button2_state_A = SDL_GameControllerGetButton(gamepad2, SDL_CONTROLLER_BUTTON_A);
	Uint8 button2_state_Y = SDL_GameControllerGetButton(gamepad2, SDL_CONTROLLER_BUTTON_Y);
	Uint8 button2_state_X = SDL_GameControllerGetButton(gamepad2, SDL_CONTROLLER_BUTTON_X);
	Uint8 button2_state_B = SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_B);
	Uint8 button2_state_START = SDL_GameControllerGetButton(gamepad2, SDL_CONTROLLER_BUTTON_START);
	Uint8 button2_STATE_Dpad_LEFT = SDL_GameControllerGetButton(gamepad2, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	Uint8 button2_STATE_Dpad_RIGHT = SDL_GameControllerGetButton(gamepad2, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	Uint8 joystick2_STATE_up = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTY) < -CONTROLLER_DEAD_ZONE;
	Uint8 joystick2_STATE_down = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTY) > CONTROLLER_DEAD_ZONE;
	Uint8 joystick2_STATE_right = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTX) > CONTROLLER_DEAD_ZONE;
	Uint8 joystick2_STATE_left = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTX) < -CONTROLLER_DEAD_ZONE;

	if (button2_state_A) {
		if (controller2_A_button == KEY_IDLE) controller2_A_button = KEY_DOWN;
		else controller2_A_button = KEY_REPEAT;
	}
	else {
		if (controller2_A_button == KEY_REPEAT || controller2_A_button == KEY_DOWN) controller2_A_button = KEY_UP;
		else controller2_A_button = KEY_IDLE;
	}

	if (button2_state_Y) {
		if (controller2_Y_button == KEY_IDLE) controller2_Y_button = KEY_DOWN;
		else controller2_Y_button = KEY_REPEAT;
	}

	else {
		if (controller2_Y_button == KEY_REPEAT || controller2_Y_button == KEY_DOWN) controller2_Y_button = KEY_UP;
		else controller2_Y_button = KEY_IDLE;
	}

	if (button2_state_X) {
		if (controller2_X_button == KEY_IDLE) controller2_X_button = KEY_DOWN;
		else controller2_X_button = KEY_REPEAT;
	}
	else {
		if (controller2_X_button == KEY_REPEAT || controller2_X_button == KEY_DOWN) controller2_X_button = KEY_UP;
		else controller2_X_button = KEY_IDLE;
	}
		if (button2_state_B) {
			if (controller2_B_button == KEY_IDLE) controller2_B_button = KEY_DOWN;
			else controller2_B_button = KEY_REPEAT;
		}
		else {
			if (controller2_B_button == KEY_REPEAT || controller2_B_button == KEY_DOWN) controller2_B_button = KEY_UP;
			else controller2_B_button = KEY_IDLE;
		}

		if (button2_state_START) {
			if (controller2_START_button == KEY_IDLE) controller2_START_button = KEY_DOWN;
			else controller2_START_button = KEY_REPEAT;
		}
		else {
			if (controller2_START_button == KEY_REPEAT || controller2_START_button == KEY_DOWN) controller2_START_button = KEY_UP;
			else controller2_START_button = KEY_IDLE;
		}

		if (button2_STATE_Dpad_LEFT) {
			if (controller2_Dpad_LEFT == KEY_IDLE) controller2_Dpad_LEFT = KEY_DOWN;
			else controller2_Dpad_LEFT = KEY_REPEAT;
		}
		else {
			if (controller2_Dpad_LEFT == KEY_REPEAT || controller2_Dpad_LEFT == KEY_DOWN) controller2_Dpad_LEFT = KEY_UP;
			else controller2_Dpad_LEFT = KEY_IDLE;
		}
		if (button2_STATE_Dpad_RIGHT) {
			if (controller2_Dpad_RIGHT == KEY_IDLE) controller2_Dpad_RIGHT = KEY_DOWN;
			else controller2_Dpad_RIGHT = KEY_REPEAT;
		}
		else {
			if (controller2_Dpad_RIGHT == KEY_REPEAT || controller2_Dpad_RIGHT == KEY_DOWN) controller2_Dpad_RIGHT = KEY_UP;
			else controller2_Dpad_RIGHT = KEY_IDLE;
		}
		if (joystick2_STATE_up) {
			if (joystick2_UP == KEY_IDLE) joystick2_UP = KEY_DOWN;
			else joystick2_UP = KEY_REPEAT;
		}
		else {
			if (joystick2_UP == KEY_REPEAT || joystick2_UP == KEY_DOWN) controller_A_button = KEY_UP;
			else joystick2_UP = KEY_IDLE;
		}
		if (joystick2_STATE_down) {
			if (joystick2_DOWN == KEY_IDLE) joystick2_DOWN = KEY_DOWN;
			else joystick2_DOWN = KEY_REPEAT;
		}
		else {
			if (joystick2_DOWN == KEY_REPEAT || joystick2_DOWN == KEY_DOWN) controller_A_button = KEY_UP;
			else joystick2_DOWN = KEY_IDLE;
		}
		if (joystick2_STATE_right) {
			if (joystick2_RIGHT == KEY_IDLE) joystick2_RIGHT = KEY_DOWN;
			else joystick2_RIGHT = KEY_REPEAT;
		}
		else {
			if (joystick2_RIGHT == KEY_REPEAT || joystick2_RIGHT == KEY_DOWN) controller_A_button = KEY_UP;
			else joystick2_RIGHT = KEY_IDLE;
		}

		if (joystick2_STATE_left) {
			if (joystick2_LEFT == KEY_IDLE) joystick2_LEFT = KEY_DOWN;
			else joystick2_LEFT = KEY_REPEAT;
		}
		else {
			if (joystick2_LEFT == KEY_REPEAT || joystick2_LEFT == KEY_DOWN) controller_A_button = KEY_UP;
			else joystick2_LEFT = KEY_IDLE;
		}

		//keyboard
		for (int i = 0; i < MAX_KEYS; ++i)
		{
			if (keys[i] == 1)
			{
				if (keyboard[i] == KEY_IDLE)
					keyboard[i] = KEY_DOWN;
				else
					keyboard[i] = KEY_REPEAT;
			}
			else
			{
				if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
					keyboard[i] = KEY_UP;
				else
					keyboard[i] = KEY_IDLE;
			}
		}

		if (keys[SDL_SCANCODE_ESCAPE]||SDL_GameControllerGetButton(gamepad,SDL_CONTROLLER_BUTTON_BACK))
			return update_status::UPDATE_STOP;

		return update_status::UPDATE_CONTINUE;
	}


// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	SDL_GameControllerClose(gamepad);
	gamepad = NULL;
	SDL_GameControllerClose(gamepad2);
	gamepad2 = NULL;
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
	return true;
}