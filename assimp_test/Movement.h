#ifndef __MOVEMENT_H
#define __MOVEMENT_H

// GLM Mathemtics
#include "vector2D.h"


bool moveTo(vector2D &curPos, const vector2D& targetPos, vector2D& curVelocity, double timeElapsed, double offset = 0);


#endif