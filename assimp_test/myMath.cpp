#include "myMath.h"

inline float degToRad(float radians)
{
	return (piOver180 * radians); 
}

//convert from radians to degrees
inline float radToDeg(float radians)
{
   //if(radians < 0)
	  // radians += 2 * PI;//2 * PI;
   radians*= 180.0 / PI;
 return radians;
}

//converts from cartesian to polar coords
point cartToPolar(float x, float y)
{
 point2D polar;

   polar.x=sqrt((x*x) + (y*y));
   polar.y= radToDeg((float)atan(y/x));
 return polar;
}

point polarToCart(point2D polar)
{
 point2D cart;
   cart.x=polar.x*cos(polar.y);
   cart.y=polar.x*sin(polar.y);
 return cart;
}


void movePolar2D(double moveDist,point2D& cartCoords, double& angle)
{
       if(angle>359)
         angle-=360;
       else if(angle<0)
         angle=360-angle;
       if(moveDist>=0)
        {
            cartCoords.x+=moveDist*cos(degToRad(angle));
            cartCoords.y += moveDist*sin(degToRad(angle));
        }
}
