
#include"systemclass.h"
int key = 0;
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE previnstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass* system = nullptr;
	bool result;
	system = new SystemClass;
	if (!system)
	{
		return 0;
	}
	result = system->Initialize();
	if (result)
	{
		system->Run();
	}
	system->Shutdown();
	delete system;
	system = nullptr;
	return 0;
}