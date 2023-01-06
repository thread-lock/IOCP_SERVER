#pragma once
#ifndef MYMATH_H
#define MYMATH_H
#include "Global.h"


#define SQUARE(x) ( (x)*(x) )
#define RAD(x) ((x)*(3.14/180))
#define ABS(x) ( ((x) < 0) ? -(x) : (x) )      
#define ROUND(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define MAX(a,b) (((a)>=(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))


struct sMatrix2X2
{
	union
	{
		struct
		{
			float _00, _01;
			float _10, _11;
		};
		float e[2][2];
	};
};

sMatrix2X2 operator*(float,const sMatrix2X2&);
sMatrix2X2 Matrix_Inverse(const sMatrix2X2&);


struct sMatrix4X4
{
	union 
	{
		struct
		{
			float _00, _01, _02, _03; 
			float _10, _11, _12, _13;
			float _20, _21, _22, _23;
			float _30, _31, _32, _33;
		};
		float e[4][4];
	};
};

sMatrix4X4 Matrix_Unit();
sMatrix4X4 Matrix_Translation(float, float, float);
sMatrix4X4 Matrix_RoatationX(float);
sMatrix4X4 Matrix_RoatationY(float);
sMatrix4X4 Matrix_RoatationZ(float);



#endif // !MYMATH_H
