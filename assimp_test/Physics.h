#pragma once

#include "GameObject.h"

/**
* @class Physics
* @brief  Manages the physics
*
*	This includes collision resolving of two object as well as
*	the collision between objects and rigid bodies
*
* @author Liam Goerke
* @version 01
* @date 23/10/2017
*
*
*
*/
class Physics
{
public:
	Physics()
	{
		gravity = -9.8;
	}
	~Physics();

	/**
	* @brief Calculates the collision between two objects
	* @param GameObject, Object 1
	* @param GameObject, Object 2
	* @param glm::vec3, the point of collision
	* @param fragmentPath, fragment file path
	*/
	void ObjectCollision(GameObject *obj1, GameObject *obj2, glm::vec3 colPoint);
	
private:
	/**
	* @brief Calculates the Inertia tensor for an object
	* @param GameObject *Obj, the object
	* @return glm::mat3, a 3x3 matrix, the inertia tensor
	*/
	glm::mat3 jCalculator(GameObject *Obj);

	float gravity;
};

