#ifndef QINDEXCOMBOBOX_H
#define QINDEXCOMBOBOX_H

#include <QComboBox>
#include <memory>
#include <vector>
#include "SQLData.h"

class QIndexComboBox : public QComboBox
{
	Q_OBJECT
	Q_PROPERTY(int dataIndex READ dataIndex WRITE setDataIndex NOTIFY dataIndexChanged)
public:
	QIndexComboBox(QWidget *parent);
	~QIndexComboBox();

	void Initialize(std::vector<std::shared_ptr<CSQLData>> *pVector,int nSoc,int nDes,TYPEDEFINE eDesType);
	
	int dataIndex() const;

Q_SIGNALS:
	void dataIndexChanged(int);

public Q_SLOTS:
	void setDataIndex(int nIndex);
	void currentIndexChangedSlot(int index);

private:
	int m_nDataIndex;
};

#endif // QINDEXCOMBOBOX_H
