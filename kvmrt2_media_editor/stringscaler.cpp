#include <QDebug>
#include "stringscaler.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H

#include <tchar.h>
#include <windows.h>

//#include <filesystem>
/*
#include <boost/filesystem/path.hpp>			
#include <boost/filesystem/operations.hpp>		
#include <boost/filesystem/fstream.hpp>			
#include <boost/filesystem/exception.hpp>		
#include <boost/filesystem/convenience.hpp>
*/
//#pragma comment(lib,"freetype.lib")
//namespace fs = boost::filesystem;

template <class BaseType, size_t FracDigits>
class fixed_point
{
    const static BaseType factor = 1 << FracDigits;
    BaseType data;

public:
    fixed_point(double d)
    {
        *this = d; // calls operator=
    }

    fixed_point& operator=(double d)
    {
        data = static_cast<BaseType>(d*factor);
        return *this;
    }

    BaseType raw_data() const
    {
        return data;
    }
};

#define FT_HAS_KERNING( face ) ( face->face_flags & FT_FACE_FLAG_KERNING )

void* CFontScaler::m_pLibrary;


CFontScaler::CFontScaler()
{
	InitFreeType();
}
CFontScaler::~CFontScaler()
{
	DeInitFreeType();
}

CFontScaler* CFontScaler::GetInstance()
{
	static CFontScaler tScaler;
	return &tScaler;
}


std::shared_ptr<unsigned char> CFontScaler::GetScaledBitmap(const char *pszFontName,int nFace,wchar_t *pString,int nFontSize,int nWidthLimit,int nHeightLimit,int *pTotalWidth,int *pTotalHeight,int nByte)
{
	int idx;
	int x, y;
	unsigned char uColor;
	int left=0,right=0;
	int width, height, nTotalHeight;
	double dRatioX,dRatioY;
	FT_Vector pen;
	FT_Vector kerning;
	pen.x=pen.y=0;
	FT_Face tFace;
	TCHAR szBuffer[256];

	std::shared_ptr<unsigned char> pByte;
	FT_Library *pLib=(FT_Library*)m_pLibrary;
	int error=FT_New_Face((*pLib),pszFontName,nFace,&tFace);
	if(error!=0)
		return pByte;


	error=FT_Set_Char_Size(tFace, nFontSize * 64, 0, 96, 96);
	if(error!=0)
		return pByte;

	bool bKerning=FT_HAS_KERNING(tFace);
	_stprintf_s(szBuffer, _countof(szBuffer), _T("%s \n"), bKerning?_T("Has kerning"):_T("dosen't have kerning"));
	OutputDebugString(szBuffer);


	FT_Fixed lRatioX=0x10000,lRatioY=0x10000;
	FT_Matrix matrix={lRatioX,0x00000,0x00000,lRatioY};

	int nStringLen=wcslen(pString);
	for (idx=0;idx<nStringLen;idx++)
	{
		right=FT_Get_Char_Index(tFace,pString[idx]);
		if(left)
		{
			FT_Get_Kerning(tFace,left,right,FT_KERNING_DEFAULT,&kerning);
			
			_stprintf_s(szBuffer, _countof(szBuffer), _T("Kerning %d \n"), kerning.x);
			OutputDebugString(szBuffer);

			pen.x+=kerning.x;
		}
		FT_Set_Transform(tFace,&matrix,&pen);
		FT_Load_Char(tFace,pString[idx],FT_LOAD_RENDER);
		nTotalHeight=tFace->size->metrics.height;
		pen.x += tFace->glyph->advance.x;
		pen.y += tFace->glyph->advance.y;

		_stprintf_s(szBuffer,_countof(szBuffer),_T("Index %d : Point %d %d advx %d advy %d\n"),right,pen.x,pen.y, tFace->glyph->advance.x, tFace->glyph->advance.y);
		OutputDebugString(szBuffer);
		left=right;
	}
	(*pTotalWidth)=(pen.x>>6);
	(*pTotalHeight)=(nTotalHeight>>6);


	dRatioX=1.0f;dRatioY=1.0f;
	if((pen.x>>6)>nWidthLimit)
	{
		dRatioX=(double)nWidthLimit/(double)(pen.x>>6);
		fixed_point<FT_Fixed,16> fXRatio(dRatioX);
		lRatioX=fXRatio.raw_data();
		(*pTotalWidth)=nWidthLimit;
	}

	if((nTotalHeight>>6)>nHeightLimit)
	{
		dRatioY=(double)nHeightLimit/(double)(nTotalHeight>>6);
		fixed_point<FT_Fixed,16> fYRatio(dRatioY);
		lRatioY=fYRatio.raw_data();
		(*pTotalHeight)=nHeightLimit;
	}
	if((*pTotalWidth)*(*pTotalHeight)*(nByte))
	{
		pByte=std::shared_ptr<unsigned char>((unsigned char*)malloc((*pTotalWidth)*(*pTotalHeight)*(nByte)),free);
	}
	else
	{
		FT_Done_Face(tFace);
		return pByte;
	}

	memset(pByte.get(),0xFF,(*pTotalWidth)*(*pTotalHeight)*(nByte));
	unsigned char *pSurface=(unsigned char *)(pByte.get());
	int nTotalCount=(*pTotalWidth)*(*pTotalHeight);
	for(int i=0;i<nTotalCount;i++)
	{
		pSurface=pSurface+(nByte-1);
		*pSurface=0x00;//Alpha Channel
		pSurface++;
	}

	/*tFace->ascender;
	tFace->size->metrics.ascender;

	tFace->height;*/

	//TCHAR szBuffer[256];
	_stprintf_s(szBuffer,_countof(szBuffer),_T("TotalCount %d Face Heignt %d ascender %d descender %d \n"),nTotalCount*4, tFace->size->metrics.height>>6, tFace->size->metrics.ascender>>6,tFace->size->metrics.descender>>6);
	OutputDebugString(szBuffer);

	nTotalCount*=4;

	pSurface=(unsigned char *)(pByte.get());
	int nXVal,nYVal;
	pen.x=pen.y=0;
	left=0;
	//unsigned char *pBuf=(unsigned char *)pSurface;
	matrix.xx=lRatioX;
	matrix.yy=lRatioY;
	//matrix={lRatioX,0x00000,0x00000,lRatioY};
	for (idx=0;idx<nStringLen;idx++)
	{
		right=FT_Get_Char_Index(tFace,pString[idx]);
		if(left)
		{
			FT_Get_Kerning(tFace,left,right,FT_KERNING_DEFAULT,&kerning);
			pen.x+=(kerning.x*dRatioX);
		}
		FT_Set_Transform(tFace,&matrix,&pen);
		FT_Load_Char(tFace,pString[idx],FT_LOAD_RENDER/*FT_LOAD_DEFAULT*/);


		width=tFace->glyph->bitmap.width;
		height=tFace->glyph->bitmap.rows;
		for (y=0;y<height;y++)
		{
			for (x=0;x<width;x++)
			{
				uColor=tFace->glyph->bitmap.buffer[y*width+x];
				if(uColor)
				{
					
					nXVal=tFace->glyph->bitmap_left+x;
					nYVal=(int)((double)(tFace->size->metrics.ascender>>6)*dRatioY)-tFace->glyph->bitmap_top+y;
					if(((*pTotalHeight)>nYVal)&&((*pTotalWidth)>nXVal))
					{
						unsigned char *pBuf=(unsigned char*)(pSurface+((nByte)*(*pTotalWidth)*nYVal)+((nByte)*nXVal));
						memset(pBuf,0xFF,nByte-1);
						pBuf+=(nByte-1);
						memset(pBuf,uColor,1);//Alpha Channel
						pBuf++;
					}
				}
			}
		}
		pen.x += tFace->glyph->advance.x;
		pen.y += tFace->glyph->advance.y;

		_stprintf_s(szBuffer, _countof(szBuffer), _T("bitmap_left %d penx %d peny %d \n"), tFace->glyph->bitmap_left, pen.x >> 6,pen.y>>6);
		OutputDebugString(szBuffer);

		left=right;
	}
	FT_Done_Face(tFace);
	return pByte;
}

int CFontScaler::GetNumFaces(const char *pszFontFile)
{
	int nFaces=-1;
	FT_Face tFace;
	FT_Library *pLib=(FT_Library*)m_pLibrary;
	int error=FT_New_Face((*pLib),pszFontFile,-1,&tFace);
	if(error!=0)
		return nFaces;
	nFaces=tFace->num_faces;
	FT_Done_Face(tFace);
	return nFaces;
}

bool CFontScaler::GetFontString(const char *pszFontFile,int nFaceIndex,char *pchFamilyName,char *pchStyleName)
{
	FT_Face tFace;
	FT_Library *pLib=(FT_Library*)m_pLibrary;
	int error=FT_New_Face((*pLib),pszFontFile,nFaceIndex,&tFace);
	if(error!=0)
		return false;
	strcpy(pchFamilyName,tFace->family_name);
	strcpy(pchStyleName,tFace->style_name);
	FT_Done_Face(tFace);
	return true;
}


bool CFontScaler::InitFreeType()
{
	if(m_pLibrary)
	{
		delete m_pLibrary;
	}
	m_pLibrary=new FT_Library();
	return !FT_Init_FreeType((FT_Library*)m_pLibrary);
}

void CFontScaler::DeInitFreeType()
{
	FT_Library *pLib=(FT_Library*)m_pLibrary;
	FT_Done_FreeType((*pLib));
	if(m_pLibrary)
	{
		delete m_pLibrary;
		m_pLibrary=new FT_Library();
	}
}