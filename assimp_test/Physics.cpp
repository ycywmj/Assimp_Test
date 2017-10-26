#include "Physics.h"

Physics::~Physics()
{
}

void Physics::ObjectCollision(GameObject *obj1, GameObject *obj2, glm::vec3 colPoint)
{
	glm::vec3 r1, r2, normal, unitNormal, impulse, directionalImpulse;
	glm::mat3 J1, J2;


	//Calculate the distance from the center of the objects to the collision point
	r1 = colPoint - obj1->GetCOM();
	r2 = colPoint - obj2->GetCOM();

	//Calculate the normal vector
	normal = glm::cross(r1, r2);

	//Normalise the normal vector
	unitNormal = glm::normalize(normal);

	//Calculate the moments of Inetia
	J1 = jCalculator(obj1);
	J2 = jCalculator(obj2);

	//compute impulse, equation 38
	//-------------------------------------------------------------------------------------
	//temporary variables to compute impulse
	glm::vec3 newV, angV1, angV2, r1unitN, r2unitN, convertedJ1, convertedJ2 ;
	float nV1V2, angVr1unitN, angVr2unitN, massPlus;
	
	//V1-V2
	newV = obj1->GetVel() - obj2->GetVel();
	
	//initial angular velocities
	angV1 = obj1->GetAngularVel();
	angV2 = obj2->GetAngularVel();
	
	//unit normal dot new Velocity
	nV1V2 = glm::dot(unitNormal, newV);

	//cross product of r1 and unitNormal
	r1unitN = glm::cross(r1, unitNormal);

	//cross product of r2 and unitNormal
	r2unitN = (glm::cross(r2, unitNormal));

	//dot product of angularVelocity1 and r1unitN
	angVr1unitN = glm::dot(angV1, r1unitN);

	//dot product of angularVelocity2 and r2unitN
	angVr2unitN = glm::dot(angV2, r2unitN);

	// 1/m1 + 1/m2 
	massPlus = (1 / (obj1->GetMass())) + (1 / (obj2->GetMass()));

	//r1unitN * by inertia matrix 1 * r1unitN
	convertedJ1 = r1unitN * J1 * r1unitN;

	//r2unitN * by inertia matrix 2 * r2unitN
	convertedJ2 = r2unitN * J2 * r2unitN;

	impulse = (-(1 + restitutionCoefficient) * (nV1V2 + angVr1unitN - angVr2unitN) )/
					(massPlus + convertedJ1 + convertedJ2);
	//-------------------------------------------------------------------------------------

	//directional Impulse: just impulse * unitNormal
	directionalImpulse = impulse * unitNormal;

	//apply calculated values to find new values
	//-------------------------------------------------------------------------------------
	glm::vec3 vec3Temp;
	//new velocity of object1
	vec3Temp = obj1->GetVel() + directionalImpulse / (obj1->GetMass());
	obj1->SetVel(vec3Temp);

	//new velocity of object2
	vec3Temp = obj2->GetVel() + directionalImpulse / (obj2->GetMass());
	obj2->SetVel(vec3Temp);

	//new Angular momentum of object1
	vec3Temp = obj1->GetAngularVel() + impulse * J1 * r1unitN;
	obj1->SetAngVel(vec3Temp);

	//new Angular momentum of object2
	vec3Temp = obj2->GetAngularVel() + impulse * J2 * r2unitN;
	obj2->SetAngVel(vec3Temp);
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

	jValue = { Ixx, 0, 0,
				0, Iyy, 0,
				0, 0, Izz };
	
	return jValue;
}
