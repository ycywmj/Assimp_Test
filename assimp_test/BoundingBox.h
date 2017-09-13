#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <string>
#include "AABB.h"
#include "GameObject.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class BoundingBox{
public:
	BoundingBox();

	void Postition(float x, float y, float z);

	void Scale(float x, float y, float z);

	void Rotate(float x, float y, float z, float degree);

	void SetBoundingBox(double size);

	bool processCollision(GameObject &obj);

private:
	glm::vec3 Pos;
	glm::vec3 Sca;
	glm::vec4 Rot;

	glm::vec3 model[8];
	static AABB boundingBox;
};

#endif