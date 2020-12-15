#include "routemaplineproperty.h"
#include "TableManage.h"
#include "DataManage.h"
#include "dataModel.h"
#include <qdebug.h>

RouteMapLineProperty::RouteMapLineProperty(const int stnCode, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	initWidget(stnCode);

	// init func
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(acceptedChanges()));
	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(rejectedChanges()));
}

RouteMapLineProperty::~RouteMapLineProperty()
{
}

void RouteMapLineProperty::initWidget(const int stnCode)
{
	auto *pTM = CTableManage::GetInstance();
	ui.comboStationInfo->Initialize(&pTM->VECTOR_CLASS(StationInformation), 0, 2, TYPE_TEXT);

	auto stnVec = pTM->m_vStationInformation;
	auto it = find_if(stnVec.begin(), stnVec.end(), findStationNameCode(stnCode));
	if(it != stnVec.end())
	{
		auto *a = dynamic_cast<StationInformation*>(it->get());
		qDebug() << a->nOrder << a->m_nTableIndex << a->nStationCode;
		ui.comboStationInfo->setCurrentIndex(a->nOrder);
	}
}

int RouteMapLineProperty::getStationCode() const
{
	int tblIndex = ui.comboStationInfo->dataIndex();
	int stnCode = -1;
	auto *pTM = CTableManage::GetInstance();
	auto stnVec = pTM->m_vStationInformation;
	auto it = find_if(stnVec.begin(), stnVec.end(), findStationNameCodeByTableIndex(tblIndex));
	if (it != stnVec.end())
	{
		auto *a = dynamic_cast<StationInformation*>(it->get());
		stnCode = a->nStationCode;
	}

	return stnCode;
}

QString RouteMapLineProperty::getStationName() const
{
	int tblIndex = ui.comboStationInfo->dataIndex();
	QString stnName = "";
	auto *pTM = CTableManage::GetInstance();
	auto stnVec = pTM->m_vStationInformation;
	auto it = find_if(stnVec.begin(), stnVec.end(), findStationNameCodeByTableIndex(tblIndex));
	if (it != stnVec.end())
	{
		auto *a = dynamic_cast<StationInformation*>(it->get());
		stnName = QString::fromStdWString(a->szStationName1);
	}

	return stnName;
}

void RouteMapLineProperty::acceptedChanges()
{
	accept();
}

void RouteMapLineProperty::rejectedChanges()
{
	reject();
}
