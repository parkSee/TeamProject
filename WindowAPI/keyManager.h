#pragma once
#include "singletonBase.h"
//=============================================================
//	## keyManager ## (Ű �Ŵ���)
//=============================================================

#define KEYMAX 256

class keyManager : public singletonBase <keyManager>
{
private:
	bool _keyUp[KEYMAX];
	bool _keyDown[KEYMAX];

public:
	//Ű�Ŵ��� �ʱ�ȭ
	HRESULT init();
	//Ű�Ŵ��� ����
	void release();

	//Ű�� �ѹ��� ���ȳ�?
	bool isOnceKeyDown(int key);
	//Ű�� �ѹ� ���ȴ� �������?
	bool isOnceKeyUp(int key);
	//Ű�� ��� �����ֳ�?
	bool isStayKeyDown(int key);
	//���Ű��?
	bool isToggleKey(int key);

	keyManager() {}
	~keyManager() {}
};

