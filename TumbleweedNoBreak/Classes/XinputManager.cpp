#include "XinputManager.h"


SednaInput::XinputController SednaInput::XinputManager::controllers[4];
SednaInput::XinputManager::XinputManager()
{
	for (int index = 0; index < 4; index++) {
		controllers[index].setControllerIndex(index);
	}
}
bool SednaInput::XinputManager::controllerConnected(int index)
{
	if (index < 0 || index >= 4)
		return false;
	XINPUT_STATE connected;
	return XInputGetState(index,&connected) == ERROR_SUCCESS;
}

SednaInput::XinputController * SednaInput::XinputManager::getController(int index)
{
	if(index >=0 && index < 4)
	return &controllers[index];
	return nullptr;
}

void SednaInput::XinputManager::update()
{

	for (int index = 0; index < 4; index++) {
		if (controllerConnected(index)) {
			controllers[index].update();
		}
	}

}
