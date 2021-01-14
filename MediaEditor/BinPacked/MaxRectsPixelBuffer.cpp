#include "MaxRectsPixelBuffer.h"
//#include "esutil.h"



MaxRectsPixelBuffer::MaxRectsPixelBuffer()
	:MaxRectsBinPack()
{
	
}

MaxRectsPixelBuffer::MaxRectsPixelBuffer(int width, int height, int bytesPerPixel,bool bGen2ndTexIdx,bool allowFlip, bool bTextureInitFromBeginning)
	: MaxRectsBinPack(width,height, allowFlip), m_nWidth(width),m_nHeight(height), m_uFrameBufferIdx(0), m_bGenFB(bGen2ndTexIdx)
{
	initializeOpenGLFunctions();
	if (m_bGenFB)
	{
		glGenTextures(2, m_uTextureIdx);
		glGenFramebuffers(1, &m_uFrameBufferIdx);
	}
	else
	{
		glGenTextures(1, m_uTextureIdx);
		m_uTextureIdx[1] = 0;;
	}

	Init(width, height, allowFlip);
	InitBuffer(width, height, bytesPerPixel);
	if (bTextureInitFromBeginning)
	{
		if (m_bGenFB)
		{
			Sync1StTextureBuffer(false);
			Init2ndTextureBuffer();
		}
		else
		{
			Sync1StTextureBuffer(false);
		}
	}
}



MaxRectsPixelBuffer::~MaxRectsPixelBuffer()
{
	if (m_bGenFB)
	{
		glDeleteTextures(2, m_uTextureIdx);
		glDeleteFramebuffers(1, &m_uFrameBufferIdx);
		memset(m_uTextureIdx, 0, sizeof(m_uTextureIdx));
	}
	else
	{
		glDeleteTextures(1, m_uTextureIdx);
		m_uTextureIdx[1] = 0;;
	}
}


unsigned char *MaxRectsPixelBuffer::GetBuffer()
{
	return m_pBuffer.get();
}

void MaxRectsPixelBuffer::InitBuffer(int width, int height,int bytesPerPixel)
{
	if(m_pBuffer.get())
		m_pBuffer.reset();
	m_pBuffer = std::shared_ptr<unsigned char>((unsigned char*)calloc(width * height * bytesPerPixel, sizeof(unsigned char)), free);
	//memset(GetBuffer(),0, width * height * bytesPerPixel);
}

unsigned int MaxRectsPixelBuffer::Get1StTextureIdx()
{
	return m_uTextureIdx[0];
}
unsigned int MaxRectsPixelBuffer::Get2ndTextureIdx()
{
	return m_uTextureIdx[1];
}

unsigned int MaxRectsPixelBuffer::GetFrameBufferIdx()
{
	return m_uFrameBufferIdx;
}


void MaxRectsPixelBuffer::Sync1StTextureBuffer(bool bBuffer)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, m_uTextureIdx[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_nWidth, m_nHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const void*)bBuffer?GetBuffer():0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool MaxRectsPixelBuffer::Init2ndTextureBuffer()
{
	if (m_uTextureIdx[1]&&(m_uFrameBufferIdx>0))
	{
		GLuint uFBId = 0;
		GLuint uRenderBuf = 0;
		glGenRenderbuffers(1, &uRenderBuf);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glBindTexture(GL_TEXTURE_2D, m_uTextureIdx[1]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_nWidth, m_nHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindFramebuffer(GL_FRAMEBUFFER, m_uFrameBufferIdx);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_uTextureIdx[1], 0);
		GLenum eRet = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (eRet != GL_FRAMEBUFFER_COMPLETE)
		{
			return false;
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return true;
	}
	return false;
}

void MaxRectsPixelBuffer::SetSubImage(int nXoffset,int nYoffset, int nWidth, int nHeight,unsigned char *pBuffer)
{
	glBindTexture(GL_TEXTURE_2D, m_uTextureIdx[0]);
	GLenum err = glGetError();
	glTexSubImage2D(GL_TEXTURE_2D, 0, nXoffset, nYoffset,nWidth,nHeight,GL_RGBA,GL_UNSIGNED_BYTE,pBuffer);
	err = glGetError();
	glBindTexture(GL_TEXTURE_2D, 0);
	err = glGetError();
}