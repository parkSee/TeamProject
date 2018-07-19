#pragma once
//=============================================================
//	## namespace MY_UTIL ##
//=============================================================

#define PI 3.141592654f		//180��
#define PI2 (PI * 2)			//360��

//���߿� �̹��� ȸ���� ����� ��
#define PI_2 (PI / 2)		//90��
#define PI_4 (PI / 4)		//45��
#define PI_8 (PI / 8)		//22.5��

namespace MY_UTIL //�̸��� ���񸾴�� �����ص� �ȴ�
{
	//���� ������ �Ÿ�
	float getDistance(float startX, float startY, float endX, float endY);
	//���� ������ ����
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
