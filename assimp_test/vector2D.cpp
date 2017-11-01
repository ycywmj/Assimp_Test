#include <fstream>
#include "myMath.h"
#include "vector2D.h"

using namespace std;

vector2D::vector2D()
{
	this->x=this->y=0.0;
}

vector2D::vector2D(float x, float y)
{
	this->x=x;
	this->y=y;
}

vector2D::vector2D(const vector2D &vec)
{
	x=vec.x;
	y=vec.y;
}

void vector2D::set(float x, float y)
{
 this->x=x;
 this->y=y;
}

bool vector2D::isZero()
{
	return (this->x==0 && this->y==0);
}
float& vector2D::operator[](unsigned short index)
{
     if(index >=0 && index <=1)
	   return *((&x)+index);
}

const vector2D& vector2D::operator=(const vector2D &vec)
{
  x = vec.x;
  y = vec.y;
  return *this;
}

bool vector2D::operator==(const vector2D &vec)const
{
 return ((x == vec.x) && (y == vec.y));
}

const bool vector2D::operator!=(const vector2D &vec) const
{
 return !(*this == vec);
}

const vector2D vector2D::operator+(const vector2D &vec) const
{
 return vector2D(x + vec.x, y + vec.y);
}

const vector2D& vector2D::operator+=(const vector2D& vec)
{    x += vec.x;
     y += vec.y;
 return *this;
}

const vector2D& vector2D::operator+=(float val)
{
	x+=val;
	y+=val;
 return *this;
}

const vector2D vector2D::operator-(const vector2D& vec) const
{    
 return vector2D(x - vec.x, y - vec.y);
}

const vector2D& vector2D::operator-(float val)
{
	x-=val;
	y-=val;
 return *this;
}

const vector2D vector2D::operator-() const
{    
 return vector2D(-x, -y);
}

const vector2D& vector2D::operator-=(const vector2D& vec)
{
   x -= vec.x;
   y -= vec.y;
 return *this;
}

const vector2D& vector2D::operator*=(float value)
{
    x*=value;
    y*=value;
  return *this;
 }

const vector2D& vector2D::operator/=(float value)
{
	  if(value!=0)
	  {
		x /= value;
		y /=value;
	  }
   
 return *this;
}

 const vector2D vector2D::operator*(float value) const
 {
  return vector2D(x*value, y*value);
 }

 const vector2D vector2D::operator*(const vector2D& vec) const
{
 return vector2D(x*vec.x, y*vec.y);
}

const vector2D vector2D::operator/(float value) const
{
	if(value==0)
		value=1;
	else
        value = 1/value;
 return vector2D(x*value, y*value);
}

const float vector2D::dotProduct(const vector2D &vec) const
{
 return x*vec.x + y*vec.y;
}

const float vector2D::length() const
{
 return (float)sqrt((float)(x*x + y*y));
}

void vector2D::setLength(float length)
{
	if(length>=1)
	{
		this->normalise();
		*this=*this*length;
	}
}

void vector2D::normalise()
{
 float len=length();
   if(len!=0)
      (*this) /=len;
}

// return angle between two vectors in radians
const float vector2D::angleInRadians(const vector2D& normalVec) const
{
 vector2D angle=*this;
 angle.normalise();
 return acosf(angle.dotProduct(normalVec));
}

// return angle between two vectors in radians
const float vector2D::angleInDegrees(const vector2D& normalVec) const
{
 return(radToDeg(angleInRadians(normalVec))); 
}

const float vector2D::lengthSqr() const
{
 return (float)(float)(x*x + y*y);
}

//truncate a magnitude to maxValue
void vector2D::trunc(float maxValue)
{ 
   if (this->length() > maxValue)
   {
	this->normalise();
	*this *= maxValue;
   } 
}

//determines theta in degrees from a vector heading
//assumes vector stores a normalised vector
float vector2D::getHeadingDegrees()
{
 vector2D heading=*this;
 heading.normalise();
 float x=heading[0];
 float y=heading[1];
 float theta=radToDeg((float)atan(y/x));
     if(y<0)
	 {
		 if(x>=0)
			 theta=360+theta;
		 if(x<0)
			 theta=180+theta;
	 }
	 if(x<0 && y>=0)
		 theta=180+theta;
 return theta;
}

ostream& operator<<(ostream& os, const vector2D& vec)
{
  os << " " << vec.x << " " << vec.y;

  return os;
}

