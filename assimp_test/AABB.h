#ifndef __AABB_H
#define __AABB_H


// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
* @class AABB
* @brief I draws a box
*
*
*
*
*
* @author ChengYu Yang
* @version 01
* @date 15/09/2017
*
*
*/
class AABB
{
public:
	/**
	* @brief  constructor
	*/
	AABB();

	/**
	* @brief  constructor with setting min and max value
	* @param minVals, min
	* @param maxVals, max
	*/
	AABB(glm::vec3 minVals, glm::vec3 maxVals);

	/**
	* @brief  create the aabb objects
	* @param vertices, vertices of the object
	* @param numVertices, amount of vertices
	*/
	void createAABB(glm::vec3 vertices[], int numVertices);

	/**
	* @brief  the point and world must be in the same coordinate system
	* @param point, first object
	* @param worldXYZ, objects in the world
	* @return true if collide, false otherwise
	*/
	bool checkCollisionWithPoint(glm::vec3 &point, glm::vec3 worldXYZ);

	/**
	* @brief  the point and world must be in the same coordinate system
	* @param point, first object
	* @param worldXYZ, objects in the world
	* @param worldXYZ2, objects in the world 2
	* @return true if collide, false otherwise
	*/
	bool checkCollision(glm::vec3 worldXYZ, AABB &aabb2, glm::vec3 worldXYZ2);

	/**
	* @brief  Find the point of collision between two objects
	* @param point, first object
	* @param worldXYZ, objects in the world
	* @param worldXYZ2, objects in the world 2
	* @return true if collide, false otherwise
	*/
	glm::vec3 getCollisionPoint(AABB &aabb1, AABB &aabb2);

private:
	/// min coordinates of the object in the local coordinate system
	glm::vec3 min; 

	/// max coordinates of the object in the local coordinate system
	glm::vec3 max; 

	
	/**
	* @brief  convert aabb to the world
	* @param aabb, aabb
	* @param worldXYZ, coordinate of the world
	* @return aabb
	*/
	AABB createWorldAABB(AABB aabb, glm::vec3 worldXYZ); 

	/**
	* @brief  the point and aabb must be in the same coordinate system
	* @param point, first object
	* @param aabb, sec object aabb
	* @return true if collide, false otherwise
	*/
	bool checkCollisionWithPoint(glm::vec3 &point, AABB &aabb); // 

};
#endif