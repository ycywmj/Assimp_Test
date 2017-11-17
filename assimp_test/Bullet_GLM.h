#pragma once

#include <btBulletDynamicsCommon.h>
#include <glm/glm.hpp>

class Bullet_GLM{
public:
	static glm::vec3 BulletVec3ToGlmVec3(const btVector3 & val){
		return (glm::vec3((float)val.getX(),
			(float)val.getY(),
			(float)val.getZ()));
	};

	static btVector3 GlmVec3ToBulletVec3(const glm::vec3 & val){
		return (btVector3(val.x, val.y, val.z));
	};
};