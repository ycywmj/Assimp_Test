#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include "Graphics.h"

class GameObject{
public:
	GameObject();

	void Load(Graphics *graphics_handler, string fname);

	void Render(Graphics *graphics_handler);

	void Postition(float x, float y, float z);

	void Scale(float x, float y, float z);

	void Rotate(float x, float y, float z, float degree);

private:
	glm::vec3 Pos;
	glm::vec3 Sca;
	glm::vec4 Rot;
};

#endif