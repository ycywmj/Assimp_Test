#include "Graphics.h"

int main()
{
	GraphicsFactory graphics_factory;
	Graphics* graphics_handler = graphics_factory.Create("OpenGL");

	graphics_handler->CreateGameWindow();

	if (graphics_handler){
		delete graphics_handler;
		graphics_handler = NULL;
	}

	return 0;
}
  