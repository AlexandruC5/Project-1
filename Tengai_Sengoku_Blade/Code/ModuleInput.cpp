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
	Uint8 button_state_A = SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_A);
	Uint8 button_state_Y = SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_Y);
	Uint8 button_state_START = SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_START);

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

	if (button_state_START) {
		if (controller_START_button == KEY_IDLE) controller_START_button = KEY_DOWN;
		else controller_START_button = KEY_REPEAT;
	}
	else {
		if (controller_START_button == KEY_REPEAT || controller_START_button == KEY_DOWN) controller_START_button = KEY_UP;
		else controller_START_button = KEY_IDLE;
	}
	for(int i = 0; i < MAX_KEYS; ++i)
	{
		if(keys[i] == 1)
		{
			if(keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	if(keys[SDL_SCANCODE_ESCAPE])
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