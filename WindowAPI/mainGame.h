#pragma once
#include "gameNode.h"
#include "player.h"	//�÷��̾� Ŭ���� ����ϱ� ����


class mainGame : public gameNode
{
private:
	player * _player;	//�÷��̾� Ŭ���� ����
	int a;
	int b;
	int c;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);



	mainGame() {}
	~mainGame() {}
};

