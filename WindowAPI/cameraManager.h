#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase<cameraManager>
{

private:
	tagInt _mapSize;	//맵사이즈

	tagFloat _target;	//타켓의 좌표

	tagFloat _shakePos;	//카메라 흔들림 좌표
	bool _isShake;		//카메라 흔들림 불값
	float _shakeTimer;	//카메라 흔들림 시간
	float _shakeStrenth;//카메라 흔들림 강도

	RECT _renderRc;		//카메라 렉트

public:

	tagFloat _pos;		//카메라 좌표

	HRESULT init();
	void release();
	void update();
	void cameraMove();	//카메라 움직임

						//카메라 타겟 설정, 딜레이 타임이 있다면 예약타겟에넣어둔다
	void connectTarget(float x, float y, float delayTime = 0.0f);

	//맵사이즈 설정자
	void setMapSize(int width, int height) { _mapSize.x = width; _mapSize.y = height; }

	//맵 사이즈 접근자
	tagInt getMapSize() { return _mapSize; }

	//렌더 렉트 접근자
	RECT getRenderRc();
	void setNullTarget(int x, int y, int width, int height)
	{
		_pos.x = x;
		_pos.y = y;
		_renderRc = RectMakeCenter(_pos.x, _pos.y, width, height);
	}
	void shakeCamera(float strenth, float time);


	cameraManager(){}
	~cameraManager(){}
};

