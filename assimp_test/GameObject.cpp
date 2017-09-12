#include "GameObject.h"


void GameObject::Load(Graphics *graphics_handler,string fname)
{

	graphics_handler->LoadModel(fname);
}

void GameObject::Render(Graphics *graphics_handler)
{
	graphics_handler->RenderModel();
}
