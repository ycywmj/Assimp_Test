#pragma once

#include "glm/glm.hpp"

class GameObject;

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
	/**
	* @brief  constructor
	*/
	Physics(){};

	/**
	* @brief  destructor
	*/
	~Physics();

	/**
	* @brief Calculates the collision between two objects
	* @param GameObject, Object 1
	* @param GameObject, Object 2
	* @param glm::vec3, the point of collision
	* @param fragmentPath, fragment file path
	*/
	static void ObjectCollision(GameObject *obj1, GameObject *obj2, glm::vec3 colPoint, glm::vec3 normal);

	/**
	* @brief Calculates the Inertia tensor for an object
	* @param GameObject *Obj, the object
	* @return glm::mat3, a 3x3 matrix, the inertia tensor
	*/
	static glm::mat3 jCalculator(GameObject *Obj);

	/**
	* @brief Calculates the Euler vec4 based on the angular velocity vec3
	* @param glm::vec3, the angular velocity
	* @return glm::vec4 Euler
	*/
	static glm::vec4 AngularVelToRotQuat(glm::vec3 AngV);

	/// gravity constant 9.81 in float
	const static float gravity;
	
	/*the coefficient of restitution(e) is:
	e = 1, perfectly elastic collision
	e = 0, perfectly inelastic collision
	0 < e < 1, real world inelastic collision
	*/
	const static float restitutionCoefficient;
};

