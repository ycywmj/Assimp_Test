#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include "Graphics.h"
#include "AABB.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GameObject{
public:
	GameObject();

	void Load(Graphics *graphics_handler, string fname);

	void Render(Graphics *graphics_handler);

	void Postition(float x, float y, float z);

	void Scale(float x, float y, float z);

	void Rotate(float x, float y, float z, float degree);

	void SetBoundingBox(double size);

	bool processCollision(GameObject &obj);

private:
	string pathName;
	//Vector3 Pos;
	//Vector3 Sca;
	//Vector4 Rot;
	glm::vec3 Pos;
	glm::vec3 Sca;
	glm::vec4 Rot;
	
	glm::vec3 model[8];
	static AABB boundingBox;
};

#endif