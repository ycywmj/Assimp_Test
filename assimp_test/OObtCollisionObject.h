#pragma once

#include <btBulletDynamicsCommon.h>
#include <string>

class GameObject;

class OObtCollisionObject : public btCollisionObject{
public:
	OObtCollisionObject(){
		attached_obj = NULL;
	};
	
	~OObtCollisionObject(){};
	OObtCollisionObject(const OObtCollisionObject & cpy){
		this->attached_obj = cpy.attached_obj;
	};

	GameObject* GetAttachObject(){ return attached_obj; };

	void SetAttachObject(GameObject* address){ attached_obj = address; };

private:
	GameObject* attached_obj;
};