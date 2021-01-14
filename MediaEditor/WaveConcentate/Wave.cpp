 // Wave.cpp: implementation of the CWave class.
//
//////////////////////////////////////////////////////////////////////

#include "Wave.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWave::CWave(string _fileName){
	extraParam = NULL;
	wave=NULL;
	fileName=_fileName;
	extraParamLength = 0;
	fact.samplesNumber=-1;
	HANDLE hF = CreateFileA(fileName.data(),GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_READONLY,NULL);
	if (hF==INVALID_HANDLE_VALUE){
		LPVOID lpMsgBuf;
		FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				GetLastError(),
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
				(LPSTR) &lpMsgBuf,
				0,
				NULL );
		string errorMsg((LPSTR) lpMsgBuf);
		LocalFree( lpMsgBuf );
		throw errorMsg.data();
	}
	DWORD dwSize=GetFileSize(hF,0);
	DWORD read;
	ReadFile(hF,(LPVOID)&riff,RIFF_SIZE,&read,NULL);
	dwSize-=read;
	ReadFile(hF,(LPVOID)&fmt,FMT_SIZE,&read,NULL);
	dwSize-=read;
	if (fmt.wFormatTag!=1){
		ReadFile(hF,(LPVOID)&extraParamLength,2,&read,NULL); //2 bytes
		dwSize-=read;
		if (extraParamLength>0){
			extraParam=new BYTE[extraParamLength];
			ReadFile(hF,(LPVOID)extraParam,extraParamLength,&read,NULL); 
			dwSize-=read;
		}
	}
	
	ReadFile(hF,(LPVOID)&data.dataID,4,&read,NULL);
	dwSize-=read;
	if (data.dataID[0]=='f' &&
		data.dataID[1]=='a' &&
		data.dataID[2]=='c' &&
		data.dataID[3]=='t'){
		ReadFile(hF,(LPVOID)&fact,FACT_SIZE,&read,NULL);
		dwSize-=read;
		ReadFile(hF,(LPVOID)&data,DATA_SIZE,&read,NULL);
		dwSize-=read;
	}
	else
	{
		ReadFile(hF,(LPVOID)&data.dataSIZE,4,&read,NULL);
		dwSize-=read;
	}
	//if(!data.dataSIZE)
	//	data.dataSIZE=dwSize;
	//datasize가 0일때의 처리 필요함!
	wave = new BYTE[data.dataSIZE];
	ReadFile(hF,(LPVOID)wave,data.dataSIZE,&read,NULL);
	CloseHandle(hF);
}
CWave::CWave(){
	extraParam = NULL;
	wave=NULL;
	fileName="";
	fact.samplesNumber=-1;
}
CWave::CWave(const CWave& w){
	init(w);
}
CWave& CWave::operator= (const CWave &w){
	init(w);
	return *this;
}
CWave::~CWave() 
{
	if (extraParam)
	{
		delete[] extraParam;
		extraParam = NULL;
	}
	if (wave)
	{
		delete[] wave;
		wave = NULL;
	}
}

CWave CWave::operator+ (const CWave &w) const{
	if (fmt.wFormatTag!=w.fmt.wFormatTag)
		throw "Can't concatenate waves with different format tags";
	CWave ret_val;
	ret_val.fmt = w.fmt;
	ret_val.riff = w.riff;
	ret_val.data = w.data;
	ret_val.data.dataSIZE= data.dataSIZE+w.data.dataSIZE;

	 
	ret_val.extraParamLength = w.extraParamLength;
	ret_val.extraParam = w.extraParam;
	ret_val.wave = new BYTE[ret_val.data.dataSIZE];
	memcpy(ret_val.wave,wave,data.dataSIZE);
	memcpy(ret_val.wave+data.dataSIZE,w.wave,w.data.dataSIZE);

	string folder = getFileFolder(fileName);
	string title1 = getFileTitle(fileName);
	string title2 = getFileTitle(w.fileName);
	
	
	ret_val.fileName = folder;
	ret_val.fileName.append(title1);
	ret_val.fileName.append(title2);
	ret_val.fileName.append(".wav");

	return ret_val;
}



void CWave::init(const CWave& w){
	fmt = w.fmt;
	riff = w.riff;
	data = w.data;
	fact = w.fact;
	fileName = w.fileName;

	extraParamLength = w.extraParamLength;
	extraParam = w.extraParam;
	wave = new BYTE[data.dataSIZE];
	memcpy(wave,w.wave,data.dataSIZE);
	
	
}


void CWave::saveToFile(){
	HANDLE hFile = CreateFileA(fileName.data(),GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	DWORD written;
	WriteFile(hFile,(LPCVOID)&riff,RIFF_SIZE,&written,NULL);
	WriteFile(hFile,(LPCVOID)&fmt,FMT_SIZE,&written,NULL);
	if (fmt.wFormatTag>1){
		WriteFile(hFile,(LPCVOID)&extraParamLength,2,&written,NULL);
		if (extraParamLength>0)
			WriteFile(hFile,(LPCVOID)extraParam,extraParamLength,&written,NULL);
	}
	if (fact.samplesNumber>-1){
		WriteFile(hFile,(LPCVOID)"fact",4,&written,NULL);
		WriteFile(hFile,(LPCVOID)&fact,FACT_SIZE,&written,NULL);
	}
	WriteFile(hFile,(LPCVOID)&data,DATA_SIZE,&written,NULL);
	WriteFile(hFile,(LPCVOID)wave,data.dataSIZE,&written,NULL);

	CloseHandle(hFile);
}

string CWave::getFileName(){
	return fileName;
}

void CWave::setFileName(string _fileName){
 	fileName=_fileName;
}

string CWave::getFileFolder(string fullPath)
{
	string::size_type last= fullPath.find_last_of("\\");
	if (last==string::npos)
		return "";
	char* buffer = new char[fullPath.size()];
	memset(buffer,0,fullPath.size());
	string::size_type copied = fullPath.copy(buffer,last+1);

	string folder(buffer);
	delete[] buffer;
	return folder;
}

string CWave::getFileTitle(string fullPath){
	int begin= fullPath.find_last_of("\\");
	if (begin ==string::npos)
		begin=-1;
	string::size_type end= fullPath.find_last_of(".");
	
	char* buffer = new char[end-begin];
	memset(buffer,0,end-begin);
	fullPath.copy(buffer,end-begin-1,begin+1);
	string title(buffer);
	delete[] buffer;
	return title;
}
