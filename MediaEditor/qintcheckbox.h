#ifndef QINTCHECKBOX_H
#define QINTCHECKBOX_H

#include <QCheckBox>

class QIntCheckBox : public QCheckBox
{
	Q_OBJECT
	Q_PROPERTY(unsigned int checkedValue READ checkedValue WRITE setCheckedValue NOTIFY checkedValueChanged)
public:
	QIntCheckBox(QWidget *parent);
	~QIntCheckBox();
	unsigned int checkedValue() const;
Q_SIGNALS:
	void checkedValueChanged(unsigned int);
private:
	unsigned int m_uCheckedValue;
public Q_SLOTS:
	void setCheckedValue(unsigned int uCheckedValue);
private slots:
	void checkedValueAccepted(bool checked);
	
};

#endif // QINTCOMBOBOX_H
