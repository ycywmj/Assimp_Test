#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include "Graphics.h"
#include "AABB.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "DrawBox.h"

class GameObject{
public:
	GameObject();

	void Load(Graphics *graphics_handler, string fname);

	void Render(Graphics *graphics_handler);

	void Postition(float x, float y, float z);

	void Scale(float x, float y, float z);

	void Rotate(float x, float y, float z, float degree);

	void SetBoundingBox(float x, float y, float z);

	bool processCollision(GameObject &obj);

	void DrawBoundingBox();

private:
	string pathName;

	glm::vec3 Pos;
	glm::vec3 Sca;
	glm::vec4 Rot;
	
	glm::vec3 model[8];
	AABB boundingBox;

	DrawBox BoxModel;
};

#endif