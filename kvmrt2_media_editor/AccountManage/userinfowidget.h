#pragma once

#include <QWidget>
#include "ui_userinfowidget.h"

class QCheckBox;

class UserInfoWidget : public QWidget
{
	Q_OBJECT

public:
	UserInfoWidget(QWidget *parent = Q_NULLPTR);
	~UserInfoWidget();

	void SetReadOnly(QCheckBox* checkBox, bool readOnly);

public slots:
	void show();
	void onChangeAccInfo();

private:
	Ui::UserInfoWidget ui;
};
