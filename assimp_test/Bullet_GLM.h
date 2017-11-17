#pragma once

#include <btBulletDynamicsCommon.h>
#include <glm/glm.hpp>

/**
* @class Bullet_GLM
* @brief this class mainly handles the convertion between bullet vec3 and glm vec3
*
* @author Kin Pan Mak
* @version 01
* @date 01/10/2017
*
*/
class Bullet_GLM{
public:
	/**
	* @brief  convert bullet vec3 to glm vec3
	* @param bullet vec3
	* @return glm vec3 
	*/
	static glm::vec3 BulletVec3ToGlmVec3(const btVector3 & val){
		return (glm::vec3((float)val.getX(),
			(float)val.getY(),
			(float)val.getZ()));
	};

	/**
	* @brief  convert glm vec3 to bullet vec3
	* @param glm vec3
	* @return bullet vec3
	*/
	static btVector3 GlmVec3ToBulletVec3(const glm::vec3 & val){
		return (btVector3(val.x, val.y, val.z));
	};
};