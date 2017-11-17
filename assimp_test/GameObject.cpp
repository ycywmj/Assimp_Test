#include "GameObject.h"

#include "World.h"

GameObject::GameObject()
{ 
	bulletBox = new OObtCollisionObject();
	Pos.x = 0; Pos.y = 0; Pos.z = 0;
	Sca.x = 1; Sca.y = 1; Sca.z = 1;
	Rot.x = 0; Rot.y = 1.0; Rot.z = 0; Rot.w = 0;
	Vel.x = 0; Vel.y = 0; Vel.z = 0;
	AngV.x = 0; AngV.y = 0; AngV.z = 0;
	mass = 10;
	COM = Pos;
	sceneBody = false;
	RenderText = false;
}

void GameObject::LoadAll(Graphics *graphics_handler, map<string, string> fs)
{
	files = fs;

	for (map<string, string>::iterator it = files.begin(); it != files.end(); ++it) {
		Load(graphics_handler, it->second);
		cout << it->second << endl;
	}
}

void GameObject::Load(Graphics *graphics_handler,string fname)
{
	pathName = fname;

	graphics_handler->LoadModel(fname);
	
}

void GameObject::Render(Graphics *graphics_handler)
{
	World* world_instance = Singleton<World>::Instance();
	this->UpdateObject(world_instance->GetDeltaTime());
	graphics_handler->RenderModel(pathName,Pos, Sca, Rot);

}

void GameObject::UpdateModel(string s)
{
	pathName = files[s];
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
	/*if (bulletBox){
		btQuaternion quat;
		quat.setRotation(btVector3(x, y, z), glm::radians(degree));
		bulletBox->getWorldTransform().setRotation(quat);
	}*/
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
}

OObtCollisionObject* GameObject::SetBulletBoundingBox(float size_x, float size_y, float size_z){


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

bool GameObject::processCollision(GameObject *obj)
{
	//glm::vec3 collisionPoint;
	if (boundingBox.checkCollision(Pos, obj->boundingBox, obj->Pos))
	{
			return true;
	}
	return false;
}

void GameObject::UpdateObject(double deltaTime)
{
	if (isCollided){
		btDelay += deltaTime;
		if (btDelay > 1.0){
			btDelay = 0.0;
			isCollided = false;
		}
	}

	Postition(Pos.x + Vel.x * deltaTime,
		Pos.y + Vel.y * deltaTime,
		Pos.z + Vel.z * deltaTime);
	// loss
	if (Vel.x > .0f) Vel.x -= linearLoss;
	else if (Vel.x < .0f) Vel.x += linearLoss;
	if (Vel.y > .0f) Vel.y -= linearLoss;
	else if (Vel.y < .0f) Vel.y += linearLoss;
	if (Vel.z > .0f) Vel.z -= linearLoss;
	else if (Vel.z < .0f) Vel.z += linearLoss;


	glm::vec3 AngVaxisDt;
	AngVaxisDt.x = AngV.x * deltaTime;
	AngVaxisDt.y = AngV.y * deltaTime;
	AngVaxisDt.z = AngV.z * deltaTime;
	glm::vec4 newRot = Physics::AngularVelToRotQuat(AngV);

	Rotate(newRot.x, newRot.y, newRot.z, Rot.w + newRot.w * deltaTime * 30);
}