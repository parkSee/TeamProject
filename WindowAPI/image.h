#pragma once
//=============================================================
//	## image ## (������ ��� ������Ʈ �ȴ�)
//=============================================================

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,		//���ҽ��� �ε�
		LOAD_FILE,				//���Ϸ� �ε�
		LOAD_EMPTY,				//���Ʈ�� �ε�
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		redID;				//���ҽ� ID
		HDC			hMemDC;				//�޸� DC
		HBITMAP		hBit;				//��Ʈ��
		HBITMAP		hOBit;				//�õ��Ʈ��
		float		x;					//�̹��� x��ǥ
		float		y;					//�̹��� y��ǥ
		int			width;				//�̹��� ����ũ��
		int			height;				//�̹��� ����ũ��
		int			currentFrameX;		//���� ������x
		int			currentFrameY;		//���� ������y
		int			maxFrameX;			//�ִ� x������ ����
		int			maxFrameY;			//�ִ� y������ ����
		int			frameWidth;			//1�������� ���α���
		int			frameHeight;		//1�������� ���α���	
		BYTE		loadType;			//�̹��� �ε�Ÿ��

		tagImage()	//������ = �ʱ�ȭ
		{
			redID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO		_imageInfo;		//�̹��� ����
	CHAR*				_fileName;		//�̹��� �̸�
	BOOL				_isTrans;		//���� ���ٰų�? (����Ÿ)
	COLORREF			_transColor;	//���� ���� RGB (����Ÿ = RGB(255, 0, 255))

	LPIMAGE_INFO		_blendImage;	//���ĺ��� �̹���
	BLENDFUNCTION		_blendFunc;		//���ĺ��� ���

	LPIMAGE_INFO		_stretchImage;	//��Ʈ��ġ�̹���

public:
	image();
	~image();

	//�� ��Ʈ������ �ʱ�ȭ
	HRESULT init(int width, int height);
	//�̹��� ���ҽ��� �ʱ�ȭ (������)
	HRESULT init(DWORD resID, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//�̹��� ���Ϸ� �ʱ�ȭ (�ֻ��)
	HRESULT init(const char* fileName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//������ �̹��� ���Ϸ� �ʱ�ȭ (�ֻ��)
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));


	//���ĺ��� �ʱ�ȭ
	HRESULT initForAlphaBlend(void);

	//����
	void release(void);

//=============================================================
//	## �Ϲݷ��� ##
//=============================================================
	void render(HDC hdc, int destX = 0, int destY = 0);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

//=============================================================
//	## ���ķ��� ##
//=============================================================
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

//=============================================================
//	## �����ӷ��� ##
//=============================================================
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

//=============================================================
//	## �������� ##
//=============================================================
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

//=============================================================
//	## ��Ʈ��ġ���� ## (�̹��� �����ϸ�)
//=============================================================
	void stretchRender(HDC hdc, int destX, int destY, float scale = 1.0f);
	void stretchFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scale = 1.0f);

//=============================================================
//	## inline ## (�ζ��� �Լ��� - ����, ����)
//=============================================================
	//DC ���
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	//�̹��� x��ǥ
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }
	//�̹��� y��ǥ
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }
	//�̹��� ������ǥ
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}
	//�̹��� ����, ����ũ��
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }
	//�ٿ�� �ڽ�(�浹�� ��Ʈ)
	inline RECT boudingBox(void)
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->width,
			(int)_imageInfo->y + _imageInfo->height };

		return rc;
	}
	inline RECT boudingBoxWithFrame(void)
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight };

		return rc;
	}

	//������ x
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	//������ y
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	//�̹��� ���������� ����, ����ũ��
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	//�ƽ������� x, y
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }
};