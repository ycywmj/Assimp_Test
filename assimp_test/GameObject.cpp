#include "GameObject.h"

//AABB GameObject::boundingBox;

GameObject::GameObject()
{ 
	bulletBox = new btCollisionObject();
	Pos.x = 0; Pos.y = 0; Pos.z = 0;
	Sca.x = 1; Sca.y = 1; Sca.z = 1;
	Rot.x = 0; Rot.y = 1.0; Rot.z = 0; Rot.w = 0;
	Vel.x = 0; Vel.y = 0; Vel.z = 0;
	AngV.x = 0; AngV.y = 0; AngV.z = 0;
	mass = 10;
	COM = Pos;
	sceneBody = false;
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
	if (bulletBox)
		bulletBox->getWorldTransform().setOrigin(btVector3(x, y, z));
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
	if (bulletBox){
		btQuaternion quat;
		quat.setRotation(btVector3(x, y, z), glm::radians(degree));
		bulletBox->getWorldTransform().setRotation(quat);
	}
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
	
	glm::vec3 BoxSize;

	BoxSize.x = x;
	BoxSize.y = y;
	BoxSize.z = z;
}

btCollisionObject* GameObject::SetBulletBoundingBox(float size_x, float size_y, float size_z){


	if (!bulletBox) {
		std::cout << "bulletBox is Null" << std::endl;
		return NULL;
	}

	bulletBox->getWorldTransform().setOrigin(btVector3(Pos.x, Pos.y, Pos.z));
	btBoxShape* box_shape = new btBoxShape(btVector3(size_x, size_y, size_z));
	bulletBox->setCollisionShape(box_shape);

	return bulletBox;
}

void GameObject::DrawBoundingBox()
{
	//BoxModel.Draw();
}

bool GameObject::processCollision(GameObject &obj, glm::vec3 *collisionPoint)
{
	//glm::vec3 collisionPoint;
	if (boundingBox.checkCollision(Pos, obj.boundingBox, obj.Pos, collisionPoint))
	{
			return true;
	}
	return false;
}

void GameObject::UpdateObject(double deltaTime)
{
	Postition(Pos.x + Vel.x * deltaTime, 
		Pos.y + Vel.y * deltaTime, 
		Pos.z + Vel.z * deltaTime);

	//cout << "position y:" << Pos.y << endl;

	glm::vec3 angVdt; 
	glm::vec4 newRot;
	angVdt.x = AngV.x * deltaTime;
	angVdt.y = AngV.y * deltaTime;
	angVdt.z = AngV.z * deltaTime;
	newRot = Physics::AngularVelToRotQuat(angVdt);

	Rotate(newRot.x, newRot.y, newRot.z, Rot.w + newRot.w);
}