#include "movement.h"
#include "myMath.h"

bool moveTo(vector2D &curPos, const vector2D& targetPos,vector2D& curVelocity, double timeElapsed,double offset)
{ 
 bool xdone=false, zdone=false;
 vector2D newPos;  

  vector2D toTarget = targetPos - curPos;  //vector between current position and target
  toTarget.normalise();                       //get heading
  vector2D pos=targetPos;
    if(!toTarget.isZero())
    {
     pos+=-(toTarget*offset);
    }
    if(curPos==pos)
	 {
	   return true;
	 }
  curVelocity=toTarget*curVelocity.length();  //new velocity
  newPos=curVelocity*timeElapsed;             //pos = vt
    //test if we have arrived at location.
    if(curPos.getX() == pos.getX())
     {
	  xdone=true;
     }
    else if(curPos.getX() < pos.getX())
	 {
		 if(curPos.getX()+newPos.getX()>=pos.getX())
			 xdone=true;
	 }
	 else if(curPos.getX()>pos.getX())
	 {
		 if(curPos.getX()+newPos.getX()<=pos.getX())
			 xdone=true;
	 }
    if(curPos.getY() == pos.getY())
	 {
		 zdone=true;
	 }
    else if(curPos.getY() < pos.getY())
	 {
		 if(curPos.getY()+newPos.getY()>=pos.getY())
			 zdone=true;
	 }
	 else if(curPos.getY()>pos.getY())
	 {
		 if(curPos.getY()+newPos.getY()<=pos.getY())
			 zdone=true;
	 }    
    if(xdone && zdone)
	{
		curPos=pos;
		return true;
	}
	else
		curPos+=newPos;
 return false;
}