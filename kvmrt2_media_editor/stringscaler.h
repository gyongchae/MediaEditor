#ifndef STRING_SCALER
#define STRING_SCALER

#include <windows.h>
#include <memory>


class CFontScaler
{
public:
	CFontScaler();
	~CFontScaler();
public:
	static CFontScaler*  GetInstance();
	std::shared_ptr<unsigned char>  GetScaledBitmap(const char *pszFontName,int nFace,wchar_t *pString,int nFontSize,int nWidthLimit,int nHeightLimt,int *pTotalWidth,int *pTotalHeight,int nBitSize);
	bool  InitFreeType();
	void  DeInitFreeType();

	int   GetNumFaces(const char *pszFontName);
	bool  GetFontString(const char *pszFontName,int nFaceIndex,char *pchFamilyName,char *pchStyleName);
private:
	static void* m_pLibrary;
};


#endif