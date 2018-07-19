#pragma once
//=============================================================
//	## namespace MY_UTIL ##
//=============================================================

#define PI 3.141592654f		//180도
#define PI2 (PI * 2)			//360도

//나중에 이미지 회전시 사용할 값
#define PI_2 (PI / 2)		//90도
#define PI_4 (PI / 4)		//45도
#define PI_8 (PI / 8)		//22.5도

namespace MY_UTIL //이름은 너희맘대로 변경해도 된다
{
	//두점 사이의 거리
	float getDistance(float startX, float startY, float endX, float endY);
	//두점 사이의 각도
	float getAngle(float startX, float startY, float endX, float endY);
};

struct tagFloat
{
	float x;
	float y;

	tagFloat() { x = 0; y = 0; }
	tagFloat(float X, float Y) { x = X; y = Y; }
};

struct tagInt
{
	int x;
	int y;

	tagInt() { x = 0; y = 0; }
	tagInt(int X, int Y) { x = X; y = Y; }
};
