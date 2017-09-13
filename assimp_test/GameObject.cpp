#include "GameObject.h"

AABB GameObject::boundingBox;

GameObject::GameObject()
{ 
	Pos.x = 0; Pos.y = 0; Pos.z = 0;
	Sca.x = 1; Sca.y = 1; Sca.z = 1;
	Rot.x = 0; Rot.y = 1.0; Rot.z = 0; Rot.w = 0;
}

void GameObject::Load(Graphics *graphics_handler,string fname)
{
	pathName = fname;
	graphics_handler->LoadModel(fname);
}

void GameObject::Render(Graphics *graphics_handler)
{
	graphics_handler->RenderModel(pathName,Pos, Sca, Rot);
}

void GameObject::Postition(float x, float y, float z)
{
	Pos.x = x;
	Pos.y = y;
	Pos.z = z;
}

void GameObject::Scale(float x, float y, float z)
{
	Sca.x = x;
	Sca.y = y;
	Sca.z = z;
}

void GameObject::Rotate(float x, float y, float z,float degree)
{
	Rot.x = x;
	Rot.y = y;
	Rot.z = z;
	Rot.w = degree;
}

void GameObject::SetBoundingBox(double size)
{
	//model[0].set(0, 0, 0);  //front face
	model[0] = glm::vec3(0, 0, 0);
	model[1] = glm::vec3(size, 0, 0);
	model[2] = glm::vec3(size, size, 0);
	model[3] = glm::vec3(0, size, 0);

	model[4] = glm::vec3(0, 0, size);  //rear face
	model[5] = glm::vec3(size, 0, size);
	model[6] = glm::vec3(size, size, size);
	model[7] = glm::vec3(0, size, size);
	boundingBox.createAABB(model, 8);
}

bool GameObject::processCollision(GameObject &obj)
{
	if (boundingBox.checkCollision(Pos, obj.boundingBox, obj.Pos))
	{
		return true;
	}
	return false;
}

