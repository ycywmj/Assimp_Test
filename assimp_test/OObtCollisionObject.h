#pragma once

#include <btBulletDynamicsCommon.h>
#include <string>

class GameObject;

/**
* @class OObtCollsionObject
* @brief inheritence from btCollisionObject, with attaching GameObject
*
* @author Kin Pan Mak
* @version 01
* @date 02/10/2017
*
*
*/
class OObtCollisionObject : public btCollisionObject{
public:
	/**
	* @brief  constructor
	*/
	OObtCollisionObject(){
		attached_obj = NULL;
	};
	
	/**
	* @brief  destructor
	*/
	~OObtCollisionObject(){};

	/**
	* @brief  copy constructor
	* @param copy object
	*/
	OObtCollisionObject(const OObtCollisionObject & cpy){
		this->attached_obj = cpy.attached_obj;
	};

	/**
	* @brief get the GameObject attached with the bullet bounding box
	* @return attached GameObject
	*/
	GameObject* GetAttachObject(){ return attached_obj; };

	/**
	* @brief set the GameObject attached with the bullet bounding box
	* @param attached GameObject
	* @return void
	*/
	void SetAttachObject(GameObject* address){ attached_obj = address; };

private:
	/// the GameObject attached with the bullet bounding box
	GameObject* attached_obj;
};