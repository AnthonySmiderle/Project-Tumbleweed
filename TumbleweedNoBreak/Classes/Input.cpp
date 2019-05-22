#include "Input.h"
#include <Windows.h>
#include "Events.h"
bool isEvent(unsigned char event)
{
	return GetAsyncKeyState(event);
}
