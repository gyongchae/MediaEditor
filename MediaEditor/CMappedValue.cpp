#include "CMappedValue.h"
#include <qdebug.h>


CMappedValue::CMappedValue()
{
	initMappedValue();
}


CMappedValue::~CMappedValue()
{
}




int CMappedValue::m_nStationCode = 0;
int CMappedValue::m_nCarNumber = 0;
int CMappedValue::m_nDestinationCode = 0;
std::map<std::wstring, int *> CMappedValue::m_mMappedValue;


CMappedValue *CMappedValue::GetInstance()
{
	static CMappedValue tDataManage;
	return &tDataManage;
}

void CMappedValue::initMappedValue()
{
	m_mMappedValue[L"STATION_NAME"] = &m_nStationCode;
	m_mMappedValue[L"DESTINATION_NAME"] = &m_nDestinationCode;
	m_mMappedValue[L"CAR_NUMBER"] = &m_nCarNumber;
	m_mMappedValue[L"STATION_NUMBER"] = &m_nStationCode;
}




bool CMappedValue::getMappedValue(wchar_t *pTagName, std::shared_ptr<CValueMonitor> *pVM)
{
	auto it = m_mMappedValue.find(pTagName);
	if (it != m_mMappedValue.end())
	{
		(*pVM) = std::shared_ptr<CValueMonitor>(new CIntValueMonitor());
		(*pVM)->setValue(it->second);
		return true;
	}
	return false;
}
void CMappedValue::setStationCode(int nValue)
{
	m_nStationCode = nValue;
}
void CMappedValue::setCarNumber(int nNumber)
{
	m_nCarNumber = nNumber;
}
void CMappedValue::setDestinationCode(int nCode)
{
	m_nDestinationCode = nCode;
}