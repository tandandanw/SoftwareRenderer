#include "SoftwareRenderer.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	Tan::SoftwareRenderer* Renderer = new Tan::SoftwareRenderer;
	if (!Renderer)
		return 0;

	bool result = Renderer->Initialize();
	if (result)
		Renderer->Run();

	Renderer->Shutdown();
	delete Renderer;
	Renderer = nullptr;

	return 0;
}