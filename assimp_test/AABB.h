#ifndef __AABB_H
#define __AABB_H


// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class AABB
{
private:
	glm::vec3 min; // min and max coordinates of the object
	glm::vec3 max; // in the local coordinate system
	AABB createWorldAABB(AABB aabb, glm::vec3 worldXYZ); // convert aabb to the world
	bool checkCollisionWithPoint(glm::vec3 &point, AABB &aabb); // the point and aabb must be in
	// the same coordinate system
public:
	AABB();
	AABB(glm::vec3 minVals, glm::vec3 maxVals);
	void createAABB(glm::vec3 vertices[], int numVertices);
	bool checkCollisionWithPoint(glm::vec3 &point, glm::vec3 worldXYZ);
	bool checkCollision(glm::vec3 worldXYZ, AABB &aabb2, glm::vec3 worldXYZ2);
	const AABB &operator=(const AABB &aabb2);
};
#endif