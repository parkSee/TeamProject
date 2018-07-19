#pragma once
#include "gameNode.h"
#include "player.h"	//플레이어 클래스 사용하기 위해


class mainGame : public gameNode
{
private:
	player * _player;	//플레이어 클래스 선언
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

