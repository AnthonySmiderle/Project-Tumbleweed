#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <cmath>

#pragma comment(lib,"Xinput.lib")

namespace Sedna {
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
		void setControllerIndex(int index);
		void update();
		void deadZoneSticks(float dz);
		void deadZoneTriggers(float dz);
		float getLStickDirection();

		void updateSticks(Stick sticks[2]);

		void getTriggers(Triggers &triggers);
		bool isButtonPressed(int button);
		bool isButtonReleased(int button);
		
		void setVibration(float left, float right);
		bool isVibrating();
	private:
		XINPUT_VIBRATION vibration;
		int index = -1;
		XINPUT_STATE state;
		float deadZoneStick, deadZoneTrigger;

	};

	class XinputManager
	{
	public:

		XinputManager();

		static bool controllerConnected(int index);

		static XinputController * getController(int index);

		static void update();
	private:
		//...

		static XinputController controllers[4];

	};
}