#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <cmath>

#pragma comment(lib,"Xinput.lib")

//Buttons used for the controllers
enum CONTROLLER_INPUT_BUTTONS
{
	DPAD_UP = XINPUT_GAMEPAD_DPAD_UP,
	DPAD_DOWN = XINPUT_GAMEPAD_DPAD_DOWN,
	DPAD_LEFT = XINPUT_GAMEPAD_DPAD_LEFT,
	DPAD_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
	A = XINPUT_GAMEPAD_A,
	B = XINPUT_GAMEPAD_B,
	X = XINPUT_GAMEPAD_X,
	Y = XINPUT_GAMEPAD_Y,
	LB = XINPUT_GAMEPAD_LEFT_SHOULDER,
	RB = XINPUT_GAMEPAD_RIGHT_SHOULDER,
	THUMB_LEFT = XINPUT_GAMEPAD_LEFT_THUMB,
	THUMB_RIGHT = XINPUT_GAMEPAD_RIGHT_THUMB,
	SELECT = XINPUT_GAMEPAD_BACK,
	START = XINPUT_GAMEPAD_START
};

enum STICK_NAMES
{
	LS,
	RS
};

enum TRIGGER_NAMES
{
	LT,
	RT
};

//The X & Y input of the controller given as a float value from -1 -> 1 
struct Stick
{
	float x, y;
};

//The left and right trigger values that are  given as a float value from 0 -> 1
struct Triggers
{
	float LT, RT;
};

class XinputController
{
public:
	//...
	void setControllerIndex(int index) {
		this->index = index;
	}
	void update() {
		if (index >= 0 && index < 4) {
			XInputGetState(index, &state);
		}
	}
	void deadZoneSticks(float dz) {
		deadZoneStick = dz;
	}
	void deadZoneTriggers(float dz) {
		deadZoneTrigger = dz;
	}

	void getSticks(Stick sticks[2]) {
		//LEFT STICK
		float x = (float)state.Gamepad.sThumbLX / 32768,
			y = (float)state.Gamepad.sThumbLX / 32767;

		if (sqrt(x*x + y * y) > deadZoneStick) {


			if (state.Gamepad.sThumbLX < 0)
				sticks[0].x = (float)state.Gamepad.sThumbLX / 32768;//conver to a float from 1 -> 1;
			else
				sticks[0].x = (float)state.Gamepad.sThumbLX / 32767;

			if (state.Gamepad.sThumbLX < 0)
				sticks[0].y = (float)state.Gamepad.sThumbLY / 32768;//conver to a float from 1 -> 1;
			else
				sticks[0].y = (float)state.Gamepad.sThumbLY / 32767;
		}

		x = (float)state.Gamepad.sThumbRX / 32768,
		y = (float)state.Gamepad.sThumbRX / 32767;
		//RIGHT STICK
		if (state.Gamepad.sThumbLX < 0) {
			if (state.Gamepad.sThumbRX < 0)
				sticks[1].x = (float)state.Gamepad.sThumbRX / 32768;//conver to a float from 1 -> 1;
			else
				sticks[1].x = (float)state.Gamepad.sThumbRX / 32767;

			if (state.Gamepad.sThumbRX < 0)
				sticks[1].y = (float)state.Gamepad.sThumbRY / 32768;//conver to a float from 1 -> 1;
			else
				sticks[1].y = (float)state.Gamepad.sThumbRY / 32767;
		}


	}

	void getTriggers(Triggers &triggers) {
		float l = (float)state.Gamepad.bLeftTrigger / 255, r = (float)state.Gamepad.bRightTrigger / 255;
		triggers = Triggers{ l < deadZoneTrigger ? 0:l,r < deadZoneTrigger ? 0:r};//converts byte to a number from 0 to 1
	}
	bool isButtonPressed(int button) {
		return button & state.Gamepad.wButtons;//bitwise &, checks if button and wButtons are equal
	}
	bool isButtonReleased(int button) {
		return !isButtonPressed(button);
	}
private:
	//...
	int index = -1;
	XINPUT_STATE state;
	float deadZoneStick, deadZoneTrigger;

};

class XinputManager
{
public:
	//...

	XinputManager();

	static bool controllerConnected(int index);

	static XinputController * getController(int index);

	static void update();
private:
	//...

	static XinputController controllers[4];

};