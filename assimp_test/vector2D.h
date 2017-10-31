#ifndef __VECTOR2D_H
#define __VECTOR2D_H

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

class vector2D
{
private:
	float x;
	float y;

public:
	 vector2D();
     vector2D(float x, float y);
     vector2D(const vector2D &vec); 
	 void set(float x, float y);
	 bool isZero();
	// vector index
	float& operator[](unsigned short index);
     // vector assignment
     const vector2D& operator=(const vector2D &vec);
     // vector equality
     bool operator==(const vector2D &vec)const;
     // vector inequality
     const bool operator!=(const vector2D &vec) const;
     // vector add
     const vector2D operator+(const vector2D &vec) const;
     // vector2D increment
     const vector2D& operator+=(const vector2D& vec);
	 const vector2D& operator+=(float val);
     // vector2D subtraction
     const vector2D operator-(const vector2D& vec) const;     
	 const vector2D& operator-(float val); 
     // vector2D negation
     const vector2D operator-() const;
     // vector2D decrement
     const vector2D &operator-=(const vector2D& vec);
     // scalar self-multiply
     const vector2D &operator*=(float value);
     // scalar self-divide
     const vector2D &operator/=(float value);
     // multiply by scalar
     const vector2D operator*(float value) const;
 	 const vector2D operator*(const vector2D& vec) const;
     // divide by scalar
     const vector2D operator/(float value) const;
	 friend ostream& operator<<(ostream& os, const vector2D& vec);
     // dot product
	 float getX()const{return x;}
	 float getY()const{return y;}
     const float dotProduct(const vector2D &vec) const;
     // length of vector2D
     const float length() const;
	 void setLength(float length);
     // normalize this vector2D
     void normalise();
     // return angle between two vectors in radians
     const float angleInRadians(const vector2D& normalVec) const;
	 // return angle between two vectors in degrees
     const float angleInDegrees(const vector2D& normalVec) const;
	 //squared length
     const float lengthSqr() const;
   	//truncate a magnitude to maxValue
  	 void trunc(float maxValue);
	 float getHeadingDegrees();
};
#endif