#pragma once
#include "gameNode.h"


class player : public gameNode
{
private:
	

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	

	player() {}
	~player() {}
};

