#include "XinputManager.h"


Sedna::XinputController Sedna::XinputManager::controllers[4];
Sedna::XinputManager::XinputManager()
{
	for (int index = 0; index < 4; index++) {
		controllers[index].setControllerIndex(index);
	}
}
bool Sedna::XinputManager::controllerConnected(int index)
{
	if (index < 0 || index >= 4)
		return false;
	XINPUT_STATE connected;
	return XInputGetState(index,&connected) == ERROR_SUCCESS;
}

Sedna::XinputController * Sedna::XinputManager::getController(int index)
{
	if(index >=0 && index < 4)
	return &controllers[index];
	return nullptr;
}

void Sedna::XinputManager::update()
{

	for (int index = 0; index < 4; index++) {
		if (controllerConnected(index)) {
			controllers[index].update();
		}
	}

}
