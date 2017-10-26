#include "AABB.h"
#include <iostream>
using namespace std;

AABB::AABB()
{
	min.x = 0;
	min.y = 0;
	min.z = 0;
	max.x = 0;
	max.y = 0;
	max.z = 0;
}

AABB::AABB(glm::vec3 minVals, glm::vec3 maxVals)
{
	min = minVals;
	max = maxVals;
}

void AABB::createAABB(glm::vec3 vertices[], int numVertices)
{
	for (int i = 0; i<numVertices; i++) {
		if (vertices[i].x<min.x)
			min.x = vertices[i].x;
		if (vertices[i].x>max.x)
			max.x = vertices[i].x;
		if (vertices[i].y<min.y)
			min.y = vertices[i].y;

		if (vertices[i].y>max.y)
			max.y = vertices[i].y;

		if (vertices[i].x<min.z)
			min.z = vertices[i].z;

		if (vertices[i].z>max.z)
			max.z = vertices[i].z;
	}
}

AABB AABB::createWorldAABB(AABB aabb, glm::vec3 worldXYZ)
{
	AABB worldAABB;
	float temp;
	temp = (float)(aabb.max.x - aabb.min.x) / 2.0;
	worldAABB.min.x = worldXYZ.x - temp;
	worldAABB.max.x = worldXYZ.x + temp;
	temp = (float)(aabb.max.y - aabb.min.y) / 2.0;
	worldAABB.min.y = worldXYZ.y - temp;
	worldAABB.max.y = worldXYZ.y + temp;
	temp = (float)(aabb.max.z - aabb.min.z) / 2.0;
	worldAABB.min.z = worldXYZ.z - temp;
	worldAABB.max.z = worldXYZ.z + temp;
	return worldAABB;
}

bool AABB::checkCollisionWithPoint(glm::vec3 &point, AABB &aabb)
// the point and the aabb must be in the same coordinate system
{
	return((point.x >= aabb.min.x) && (point.x <= aabb.max.x) &&
		(point.y >= aabb.min.y) && (point.y <= aabb.max.y) &&
		(point.z >= aabb.min.z) && (point.z <= aabb.max.z));
}
bool AABB::checkCollisionWithPoint(glm::vec3 &point, glm::vec3 worldXYZ)
// check the point in the world with the current bounding box centred at wordXYZ
{
	AABB worldAABB = createWorldAABB(*this, worldXYZ);
	return((point.x >= worldAABB.min.x) && (point.x <= worldAABB.max.x) &&
		(point.y >= worldAABB.min.y) && (point.y <= worldAABB.max.y) &&
		(point.z >= worldAABB.min.z) && (point.z <= worldAABB.max.z));
}

bool AABB::checkCollision(glm::vec3 worldXYZ, AABB &aabb2, glm::vec3 worldXYZ2)
{
	AABB obj1 = createWorldAABB(*this, worldXYZ);
	AABB obj2 = createWorldAABB(aabb2, worldXYZ2);

	if (obj1.max.x<obj2.min.x || obj2.max.x<obj1.min.x)
		return false; // no collision
	if (obj1.max.y<obj2.min.y || obj2.max.y<obj1.min.y)
		return false; // no collision
	if (obj1.max.z<obj2.min.z || obj2.max.z<obj1.min.z)
		return false; // no collision
	/*glm::vec3 testvec;
	testvec = getCollisionPoint(obj1, obj2);
	std::cout << "collision occurred at point: X:" << testvec.x << " Y: "<< testvec.y 
		<< "Z: " << testvec.z << endl; */
	
	return true; // collision 
}

glm::vec3 AABB::getCollisionPoint(AABB &obj1, AABB &obj2)
{
	glm::vec3 collisionPoint;

	//if the objects collide on the X plane
	if (obj1.min.x <= obj2.max.x && obj1.max.x >= obj2.min.x)
	{
		//case 1: if obj1 is completely within obj 2
		if (obj1.min.x >= obj2.min.x && obj1.max.x <= obj2.max.x)
		{
			collisionPoint.x = obj1.max.x - 0.5 * (obj1.max.x - obj1.min.x);
		}
		//case 2: if obj2 is completely within obj 1
		if (obj2.min.x >= obj1.min.x && obj2.max.x <= obj1.max.x)
		{
			collisionPoint.x = obj2.max.x - 0.5 * (obj2.max.x - obj2.min.x);
		}
		//case 3: if obj1 max is within obj2 but not obj1 min
		if (obj1.max.x >= obj2.min.x && obj1.min.x < obj2.min.x)
		{
			collisionPoint.x = obj1.max.x - 0.5 * (obj1.max.x - obj2.min.x);
		}
		//case 4: if obj2 max is within obj1 but not obj2 min
		if (obj2.max.x >= obj1.min.x && obj2.min.x < obj1.min.x)
		{
			collisionPoint.x = obj2.max.x - 0.5 * (obj2.max.x - obj1.min.x);
		}
	}
	//if the objects collide on the Y plane
	if (obj1.min.y <= obj2.max.y && obj1.max.y >= obj2.min.y)
	{
		//case 1: if obj1 is completely within obj 2
		if (obj1.min.y >= obj2.min.y && obj1.max.y <= obj2.max.y)
		{
			collisionPoint.y = obj1.max.y - 0.5 * (obj1.max.y - obj1.min.y);
		}
		//case 2: if obj2 is completely within obj 1
		if (obj2.min.y >= obj1.min.y && obj2.max.y <= obj1.max.y)
		{
			collisionPoint.y = obj2.max.y - 0.5 * (obj2.max.y - obj2.min.y);
		}
		//case 3: if obj1 max is within obj2 but not obj1 min
		if (obj1.max.y >= obj2.min.y && obj1.min.y < obj2.min.y)
		{
			collisionPoint.y = obj1.max.y - 0.5 * (obj1.max.y - obj2.min.y);
		}
		//case 4: if obj2 max is within obj1 but not obj2 min
		if (obj2.max.y >= obj1.min.y && obj2.min.y < obj1.min.y)
		{
			collisionPoint.y = obj2.max.y - 0.5 * (obj2.max.y - obj1.min.y);
		}
	}
	//if the objects collide on the Z plane
	if (obj1.min.z <= obj2.max.z && obj1.max.z >= obj2.min.z)
	{
		//case 1: if obj1 is completely within obj 2
		if (obj1.min.z >= obj2.min.z && obj1.max.z <= obj2.max.z)
		{
			collisionPoint.z = obj1.max.z - 0.5 * (obj1.max.z - obj1.min.z);
		}
		//case 2: if obj2 is completely within obj 1
		if (obj2.min.z >= obj1.min.z && obj2.max.z <= obj1.max.z)
		{
			collisionPoint.z = obj2.max.z - 0.5 * (obj2.max.z - obj2.min.z);
		}
		//case 3: if obj1 max is within obj2 but not obj1 min
		if (obj1.max.z >= obj2.min.z && obj1.min.z < obj2.min.z)
		{
			collisionPoint.z = obj1.max.z - 0.5 * (obj1.max.z - obj2.min.z);
		}
		//case 4: if obj2 max is within obj1 but not obj2 min
		if (obj2.max.z >= obj1.min.z && obj2.min.z < obj1.min.z)
		{
			collisionPoint.z = obj2.max.z - 0.5 * (obj2.max.z - obj1.min.z);
		}
	}

	return collisionPoint;
}