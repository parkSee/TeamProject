#include "stdafx.h"
#include "bullet.h"
//=============================================================
//	## bullet ## (�����Ѿ� - ������� ����� �ȴ�)
//=============================================================
HRESULT bullet::init(const char * imageName, int bulletMax, float range)
{
	//�Ѿ� �̹��� �ʱ�ȭ
	_imageName = imageName;
	//�Ѿ˰��� �� ��Ÿ� �ʱ�ȭ
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void bullet::release(void)
{
}

void bullet::update(void)
{
	this->move();
}

void bullet::render(void)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

void bullet::fire(float x, float y, float angle, float speed)
{
	//�Ѿ� ���Ϳ� ��°��� ��������
	if (_bulletMax < _vBullet.size() + 1) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = speed;
	bullet.angle = angle;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());

	//���Ϳ� ���
	_vBullet.push_back(bullet);
}

void bullet::move()
{
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		//�Ѿ��� ��Ÿ����� Ŀ������
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y);
		if (_range < distance)
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

void bullet::removeBullet(int index)
{
	_vBullet.erase(_vBullet.begin() + index);
}


//=============================================================
//	## missile ## (missile[0] -> �迭ó�� �̸� �����صΰ� �Ѿ˹߻�)
//=============================================================
HRESULT missile::init(int bulletMax, float range)
{
	//��Ÿ�, �Ѿ˰��� �ʱ�ȭ
	_range = range;
	_bulletMax = bulletMax;

	//�Ѿ��� ������ŭ ����ü�� �ʱ�ȭ �� �� ���Ϳ� ���
	for (int i = 0; i < bulletMax; i++)
	{
		//�Ѿ� ����ü ����
		tagBullet bullet;
		//���θ޸� �Ǵ� ���
		//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("missile.bmp", 25, 124, true, RGB(255, 0, 255));
		bullet.speed = 5.0f;
		bullet.fire = false;

		//���Ϳ� ���
		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void missile::release(void)
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].bulletImage->release();
		SAFE_DELETE(_vBullet[i].bulletImage);
	}
}

void missile::update(void)
{
	this->move();
}

void missile::render(void)
{
	/*
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (!_vBullet[i].fire) continue;
		_vBullet[i].bulletImage->render(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
	}
	*/

	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

void missile::fire(float x, float y)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;

		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());
		break;
	}
}

void missile::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;

		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		//�Ѿ��� ��Ÿ����� Ŀ������ 
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y);
		if (_range < distance)
		{
			_viBullet->fire = false;
		}
	}
}

//=============================================================
//	## missileM1 ## (��źó�� �ѹ߾� �߻��ϸ鼭 �����ϰ� �ڵ�����)
//=============================================================
HRESULT missileM1::init(int bulletMax, float range)
{
	//�Ѿ˰���, ��Ÿ� �ʱ�ȭ
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void missileM1::release(void)
{
}

void missileM1::update(void)
{
	move();
}

void missileM1::render(void)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	
		_viBullet->count++;
		if (_viBullet->count % 3 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

void missileM1::fire(float x, float y)
{
	//�Ѿ� ���Ϳ� ��°��� ��������
	if (_bulletMax < _vBullet.size() + 1) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage->init("missile.bmp", 416, 64, 13, 1);
	bullet.speed = 5.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth(),
		bullet.bulletImage->getFrameHeight());

	//���Ϳ� ���
	_vBullet.push_back(bullet);
}

void missileM1::move()
{
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		//�Ѿ��� ��Ÿ����� Ŀ������
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y);
		if (_range < distance)
		{
			_viBullet->bulletImage->release();
			SAFE_DELETE(_viBullet->bulletImage);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

void missileM1::removeMissileM1(int index)
{
	_vBullet[index].bulletImage->release();
	SAFE_DELETE(_vBullet[index].bulletImage);
	_vBullet.erase(_vBullet.begin() + index);
}


