#include "GameObject.h"

//AABB GameObject::boundingBox;

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

void GameObject::SetBoundingBox(float x, float y, float z)
{
	//model[0].set(0, 0, 0);  //front face
	model[0] = glm::vec3(0, 0, 0);
	model[1] = glm::vec3(x, 0, 0);
	model[2] = glm::vec3(x, y, 0);
	model[3] = glm::vec3(0, y, 0);

	model[4] = glm::vec3(0, 0, z);  //rear face
	model[5] = glm::vec3(x, 0, z);
	model[6] = glm::vec3(x, y, z);
	model[7] = glm::vec3(0, y, z);
	boundingBox.createAABB(model, 8);

	BoundingBoxLengths.x = x;
	BoundingBoxLengths.y = y;
	BoundingBoxLengths.z = z;
	/*
	glm::vec3 BoxSize;
	BoxSize.x = x;
	BoxSize.y = y;
	BoxSize.z = z;
	BoxModel.LoadBox(Pos, BoxSize);*/
}

void GameObject::DrawBoundingBox()
{
	BoxModel.Draw();
}

bool GameObject::processCollision(GameObject &obj)
{
	if (boundingBox.checkCollision(Pos, obj.boundingBox, obj.Pos))
	{
		return true;
	}
	return false;
}
