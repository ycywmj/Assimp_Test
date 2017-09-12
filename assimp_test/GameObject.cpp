#include "GameObject.h"

GameObject::GameObject()
{ 
	Pos.x = 0; Pos.y = 0; Pos.z = 0;
	Sca.x = 1; Sca.y = 1; Sca.z = 1;
	Rot.x = 0; Rot.y = 0; Rot.z = 0; Rot.w = 0;
}

void GameObject::Load(Graphics *graphics_handler,string fname)
{

	graphics_handler->LoadModel(fname);
}

void GameObject::Render(Graphics *graphics_handler)
{
	graphics_handler->RenderModel(Pos, Sca, Rot);
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