#pragma once
#include "MaxRectsBinPack.h"
#include <qopenglfunctions.h>
#include <memory>


class MaxRectsPixelBuffer
	:public rbp::MaxRectsBinPack, protected QOpenGLFunctions
{
public:
	MaxRectsPixelBuffer();
	MaxRectsPixelBuffer(int width, int height, int bytesPerPixel, bool bGet2ndTexIdx=false,bool allowFlip=true,bool bTextureInitFromBeginning=false);
	void InitBuffer(int width, int height, int bytesPerPixel);
	unsigned char *GetBuffer();
	virtual ~MaxRectsPixelBuffer();
	unsigned int Get1StTextureIdx();
	unsigned int Get2ndTextureIdx();
	unsigned int GetFrameBufferIdx();
	void Sync1StTextureBuffer(bool bBuffer=true);
	bool Init2ndTextureBuffer();
	void SetSubImage(int nXoffset, int nYoffset, int nWidth, int nHeight, unsigned char *pBuffer);
private:
	int m_nWidth;
	int m_nHeight;
	bool m_bGenFB;
	std::shared_ptr<unsigned char> m_pBuffer;
	unsigned int m_uTextureIdx[2];
	unsigned int m_uFrameBufferIdx;
};

