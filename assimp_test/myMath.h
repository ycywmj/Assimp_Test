#ifndef __MYMATH_H
#define __MYMATH_H

#include <math.h>

#define PI 3.14159265358979323846
#define piOver180 PI/180

typedef struct point{double x; double y;}point2D;

inline float degToRad(float radians);
//convert from radians to degrees
inline float radToDeg(float radians);
//converts from cartesian to polar coords
point cartToPolar(float x, float y);
point polarToCart(point2D polar);
void movePolar2D(double moveDist,point2D& cartCoords, double& angle);
#endif
