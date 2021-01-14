#ifndef MAPPEDVALUE
#define MAPPEDVALUE

#include <map>
#include <memory>
#include "ValueMonitor.h"

class CMappedValue
{
public:
	CMappedValue();
	~CMappedValue();

	static CMappedValue *GetInstance();
public:
	static bool getMappedValue(wchar_t *pTagName, std::shared_ptr<CValueMonitor> *pVM);
	static void setStationCode(int nValue);
	static void setCarNumber(int nNumber);
	static void setDestinationCode(int nCode);
private:
	static void initMappedValue();
	static int m_nStationCode;
	static int m_nCarNumber;
	static int m_nDestinationCode;
	static std::map<std::wstring, int *> m_mMappedValue;
};

#endif