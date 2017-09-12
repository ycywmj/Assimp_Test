#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include "Graphics.h"

class GameObject{
public:
	GameObject(){};

	void Load(Graphics *graphics_handler, string fname);

	void Render(Graphics *graphics_handler);

private:
	GraphicsFactory graphics_factory;

};

#endif