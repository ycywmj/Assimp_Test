#include "Physics.h"

Physics::~Physics()
{
}

void Physics::ObjectCollision(GameObject *obj1, GameObject *obj2, glm::vec3 colPoint)
{
	glm::vec3 r1, r2, normal, unitNormal;
	glm::mat3 J1, J2;


	//Calculate the distance from the center of the objects to the collision point
	r1 = colPoint - obj1->GetCOM();
	r2 = colPoint - obj2->GetCOM();

	//Calculate the normal vector
	normal = glm::cross(r1, r2);

	//Normalise the normal vector
	unitNormal = glm::normalize(normal);

	//Calculate the moments of Inetia
	

}

glm::mat3 Physics::jCalculator(GameObject *Obj)
{
	float xLength, yLength, zLength;
	float Ixx, Iyy, Izz;
	glm::mat3 jValue;

	//get the lengths of the sides of the bounding box
	xLength = Obj->GetBBLengths().x;
	yLength = Obj->GetBBLengths().y;
	zLength = Obj->GetBBLengths().z;
	
	//calculate the initia values for x, y, z
	Ixx = (1 / 12) * (Obj->GetMass()) * (yLength*yLength + zLength*zLength);
	Iyy = (1 / 12) * (Obj->GetMass()) * (xLength*xLength + zLength*zLength);
	Izz = (1 / 12) * (Obj->GetMass()) * (xLength*xLength + yLength*yLength);

	return jValue;
}
