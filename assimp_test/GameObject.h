#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include "Graphics.h"
#include "AABB.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "DrawBox.h"


/**
* @class GameObject
* @brief GameObject does stuff
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

class GameObject{
public:

	/**
	* @brief  constructor
	*/
	GameObject();

	/**
	* @brief  Load the model file and bind as this game object
	* @param graphics_handler, using specific graphics api same as the entire game program to load the model
	* @param fname, path with file name of the model
	* @return void
	*/
	void Load(Graphics *graphics_handler, string fname);

	/**
	* @brief  Render the model of this game object
	* @param graphics_handler, using specific graphics api same as the entire game program to render the model
	* @return void
	*/
	void Render(Graphics *graphics_handler);

	/**
	* @brief  Set the game object's position
	* @param x, value in x-axis
	* @param y, value in y-axis
	* @param z, value in z-axis
	* @return void
	*/
	void Postition(float x, float y, float z);

	/**
	* @brief  Set the game object's scaling value
	* @param x, value in x-axis
	* @param y, value in y-axis
	* @param z, value in z-axis
	* @return void
	*/
	void Scale(float x, float y, float z);

	/**
	* @brief  Set the game object's rotation value
	* @param x, value in x-axis
	* @param y, value in y-axis
	* @param z, value in z-axis
	* @return void
	*/
	void Rotate(float x, float y, float z, float degree);

	/**
	* @brief  Set the game object's bounding box by passing its size
	* @param x, size in x-axis
	* @param y, size in y-axis
	* @param z, size in z-axis
	* @return void
	*/
	void SetBoundingBox(float x, float y, float z);

	/**
	* @brief  Determine the collision happens between 2 objs
	* @param obj, target object
	* @return bool, true if collide, false otherwise
	*/
	bool processCollision(GameObject &obj);
	
	void DrawBoundingBox();

private:
	/// path of the model file
	string pathName;

	/// Position
	glm::vec3 Pos;
	/// Scale
	glm::vec3 Sca;
	/// Rotation
	glm::vec4 Rot;
	
	/// Bounding Box vertices
	glm::vec3 model[8];
	/// Bounding Box
	AABB boundingBox;

	DrawBox BoxModel;
};

#endif