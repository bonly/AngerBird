/**
 *  @file pre.cpp
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */

#include "pre.h"
#include "Configure.h"
float getWorldNum(int num)
{
  return ((float)((float)num/(float32)CONF.PTM));
}

float getPixNum(float num)
{
  return num * (CONF.PTM);
}

int getImagePosFromAngle(float angle)
{
	int result;
	int i=0; 
	for (i =0; i< 20; i++)
	{
		if (angle < -360.0f)
			angle = -360.0f  - angle;
		else if (angle > 360.0f)
			angle = angle-360.0f;
		else
			break;
	}

	if (angle < 0.0f)
		angle = 360+angle;
	//
	if (angle > 180.0f)
		angle = angle-180.0f;  // 355-180=175  / 5 = 35
	//
	float32 n= angle/5.0f;
	int n1 = angle/5;
	float32 rest = n-(float32)n1;
	if (rest > 0.5f)
		result= n1+1;
	else
		result= n1;
	if (result == 36)
		result = 0;

	return result;
}

float32 sin2oc(float32 sinv)
{
  float32 res = sinv*(180.f/b2_pi);
  return ceill(res);
}
//} /* namespace NBird */
