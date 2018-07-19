#include "stdafx.h"
#include "cameraManager.h"

HRESULT cameraManager::init()
{
	_pos.x = WINSIZEX / 2;
	_pos.y = WINSIZEY / 2;

	_renderRc = RectMakeCenter(_pos.x, _pos.y, WINSIZEX, WINSIZEY);

	_mapSize.x = WINSIZEX;
	_mapSize.y = WINSIZEY;

	_shakeStrenth = 0;
	_shakeTimer = 0;
	
	_isShake = false;
	_shakePos = tagFloat(0, 0);
	_shakeTimer = 0;
	_shakeStrenth = 0;

	return S_OK;
}

void cameraManager::release()
{
}

void cameraManager::update()
{

	this->cameraMove();

	if (_renderRc.left < 0)
	{
		_pos.x -= _renderRc.left;
	}
	if (_renderRc.right > _mapSize.x)
	{
		_pos.x -= _renderRc.right - _mapSize.x;
	}
	if (_renderRc.top < 0)
	{
		_pos.y -= _renderRc.top;
	}
	if (_renderRc.bottom > _mapSize.y)
	{
		_pos.y -= _renderRc.bottom - _mapSize.y;
	}


}

void cameraManager::cameraMove()
{
	_pos.x = _target.x;
	_pos.y = _target.y;
	if (_isShake)
	{
		static int dir = 1;

		//_shakeTimer -= TIMEMANAGER->getElapsedTime();
		_shakeTimer -= 0.1f;

		_shakePos.x += _shakeStrenth * dir;
		_shakePos.y += _shakeStrenth * dir;

		dir *= -1;

		if (_shakeTimer < 0)
		{
			_isShake = false;
			_shakePos = tagFloat(0, 0);
			_shakeTimer = 0;
		}
	}

	//랜더 렉트 좌표 초기화
	_renderRc = RectMakeCenter(_pos.x, _pos.y, WINSIZEX, WINSIZEY);

}

void cameraManager::connectTarget(float x, float y, float delayTime)
{
	if (delayTime <= 0.0f)
	{
		_target.x = x;
		_target.y = y;
	}
}

RECT cameraManager::getRenderRc()
{
	_renderRc = RectMakeCenter(_pos.x, _pos.y, WINSIZEX, WINSIZEY);

	return _renderRc;
}

void cameraManager::shakeCamera(float strenth, float time)
{
	_shakeTimer = time;
	_isShake = true;
	_shakeStrenth = strenth;

}
