#ifndef __VECTOR2D_H
#define __VECTOR2D_H

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

/**
* @class vector2D
* @brief our own vector2 class for AI usage (emotion system)
*
* @author ChengYu Yang
* @version 01
* @date 01/10/2017
*
*
*/
class vector2D
{
private:
	/// x value
	float x;
	/// y value
	float y;

public:
	/**
	* @brief  constructor
	*/
	 vector2D();
	 /**
	 * @brief  constructor with init x and y value
	 * @param x: init x value
	 * @param y: init y value
	 */
     vector2D(float x, float y);
	 /**
	 * @brief  copy constructor
	 * @param vec: copy
	 */
     vector2D(const vector2D &vec); 

	 void set(float x, float y);
	 /**
	 * @brief  check if the vec2 object is zero
	 * @return true if is zero
	 */
	 bool isZero();
	 /**
	 * @brief  vector index
	 * @param index of the value
	 * @return value at the index
	 */
	 float& operator[](unsigned short index);
	 /**
	 * @brief  vector assignment
	 * @return back to the left side
	 */
     const vector2D& operator=(const vector2D &vec);
	 /**
	 * @brief  vector equality
	 * @param  compare target
	 * @return true if they are equal
	 */
     bool operator==(const vector2D &vec)const;
	 /**
	 * @brief  vector inequality
	 * @param  compare target
	 * @return true if they are inequal
	 */
     const bool operator!=(const vector2D &vec) const;
	 /**
	 * @brief  vector add
	 * @param  add target
	 * @return back to the left side
	 */
     const vector2D operator+(const vector2D &vec) const;
	 /**
	 * @brief  vector increment
	 * @param  increment target in vec2
	 * @return back to the left side
	 */
     const vector2D& operator+=(const vector2D& vec);
	 /**
	 * @brief  vector increment
	 * @param  increment target in float
	 * @return back to the left side
	 */
	 const vector2D& operator+=(float val);
	 /**
	 * @brief  vector2D subtraction
	 * @param  subtraction target in vec2
	 * @return back to the left side
	 */
     const vector2D operator-(const vector2D& vec) const;     
	 /**
	 * @brief  vector2D subtraction
	 * @param  subtraction target in float
	 * @return back to the left side
	 */
	 const vector2D& operator-(float val); 
     // vector2D negation
     const vector2D operator-() const;
	 /**
	 * @brief  vector decrement
	 * @param  decrement target in vec2
	 * @return back to the left side
	 */
     const vector2D &operator-=(const vector2D& vec);
	 /**
	 * @brief  scalar self-multiply
	 * @param  multiply target
	 * @return back to the left side
	 */
     const vector2D &operator*=(float value);
	 /**
	 * @brief  scalar self-divide
	 * @param  divide target
	 * @return back to the left side
	 */
     const vector2D &operator/=(float value);
	 /**
	 * @brief  multiply by scalar
	 * @param  multiply target in float
	 * @return back to the left side
	 */
     const vector2D operator*(float value) const;
	 /**
	 * @brief  multiply by scalar
	 * @param  multiply target in vec2
	 * @return back to the left side
	 */
 	 const vector2D operator*(const vector2D& vec) const;
	 /**
	 * @brief  divide by scalar
	 * @param  divide target
	 * @return back to the left side
	 */
     const vector2D operator/(float value) const;
	 /**
	 * @brief  output operator override
	 * @param  output stream
	 * @param vec2
	 * @return back to the left side
	 */
	 friend ostream& operator<<(ostream& os, const vector2D& vec);
	 float getX()const{ return x; };
	 float getY()const{ return y; };
	 /**
	 * @brief  dot product
	 * @param  vec2 target
	 * @return result value in float
	 */
     const float dotProduct(const vector2D &vec) const;
	 /**
	 * @brief  get the length of a vec2
	 * @return length of vec2 which is 2
	 */
     const float length() const;
	 /**
	 * @brief  set the length of a vec2
	 * @param new value of length
	 */
	 void setLength(float length);
	 /**
	 * @brief  normalize this vector2D
	 * @return void
	 */
     void normalise();
	 /**
	 * @brief  return angle between two vectors in radians
	 * @return angle in float
	 */
     const float angleInRadians(const vector2D& normalVec) const;
	 /**
	 * @brief  return angle between two vectors in degrees
	 * @return angle in float
	 */
     const float angleInDegrees(const vector2D& normalVec) const;
	 /**
	 * @brief  squared length
	 * @return length
	 */
     const float lengthSqr() const;
	 /**
	 * @brief  truncate a magnitude to maxValue
	 * @return void
	 */
  	 void trunc(float maxValue);
	 float getHeadingDegrees();
};
#endif