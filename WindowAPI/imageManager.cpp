#include "stdafx.h"
#include "imageManager.h"

HRESULT imageManager::init()
{
	return S_OK;
}

void imageManager::release()
{
	this->deleteAll();
}

//빈 비트맵으로 초기화
image * imageManager::addImage(string strKey, int width, int height)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	//없으면 이미지 새로 생성
	img = new image;
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL 맵의 핵심*/
	//키, 값 을 잊지 말도록!!!
	//첫번째 = 키 -> first
	//두번째 = 값(밸류) -> second
	//데이터를 추가할때 키,밸류를 쌍으로 집어넣어야 한다
	//pair, make_pair를 사용해서 추가한다
	
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}
//이미지 파일로 초기화 (주사용)
image * imageManager::addImage(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	//없으면 이미지 새로 생성
	img = new image;
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//STL 맵안에 이미지를 담아놓기
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	//없으면 이미지 새로 생성
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//STL 맵안에 이미지를 담아놓기
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//프레임 이미지 파일로 초기화 (주사용)
image * imageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	//없으면 이미지 새로 생성
	img = new image;
	if (FAILED(img->init(fileName, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//STL 맵안에 이미지를 담아놓기
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	//없으면 이미지 새로 생성
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//STL 맵안에 이미지를 담아놓기
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//이미지 키값으로 찾기
image * imageManager::findImage(string strKey)
{
	//해당키 검색
	mapImageIter key = _mImageList.find(strKey);

	//검색한 키를 찾았다면 이미지클래스 리턴
	if (key != _mImageList.end())
	{
		return key->second;
	}

	//검색한 키로 이미지를 못찾았다면 NULL;
	return NULL;
}

//이미지 키값으로 삭제
BOOL imageManager::deleteImage(string strKey)
{
	//해당키 검색
	mapImageIter key = _mImageList.find(strKey);

	//검색한 키를 찾았다면 이미지클래스 삭제
	if (key != _mImageList.end())
	{
		//이미지 해제
		key->second->release();
		//메모리 해제
		SAFE_DELETE(key->second);
		//맵의 반복자 삭제
		_mImageList.erase(key);

		return TRUE;
	}

	return FALSE;
}

//이미지 전체 삭제
BOOL imageManager::deleteAll()
{
	//맵 전체를 돌면서 하나씩 전부 지운다
	mapImageIter iter = _mImageList.begin();
	//for(;;) => while(true)
	for (;iter != _mImageList.end();)
	{
		//이미지가 있으니 이미지 클래스 삭제
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else//이미지가 없으면
		{
			++iter;
		}
	}

	//맵 전체를 삭제
	_mImageList.clear();

	return TRUE;
}

//=============================================================
//	## 일반렌더 ##
//=============================================================
void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수로 렌더시키면 됨
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수로 렌더시키면 됨
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

//=============================================================
//	## 알파렌더 ##
//=============================================================
void imageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수로 렌더시키면 됨
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수로 렌더시키면 됨
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수로 렌더시키면 됨
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

//=============================================================
//	## 프레임렌더 ##
//=============================================================
void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수로 렌더시키면 됨
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수로 렌더시키면 됨
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수로 렌더시키면 됨
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void imageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수로 렌더시키면 됨
	image* img = findImage(strKey);
	if (img) img->loopAlphaRender(hdc, drawArea, offsetX, offsetY, alpha);
}

void imageManager::stretchRender(string strKey, HDC hdc, int destX, int destY, float scale)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수로 렌더시키면 됨
	image* img = findImage(strKey);
	if (img) img->stretchRender(hdc, destX, destY, scale);
}

void imageManager::stretchFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scale)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수로 렌더시키면 됨
	image* img = findImage(strKey);
	if (img) img->stretchFrameRender(hdc, destX, destY, currentFrameX, currentFrameY, scale);
}
