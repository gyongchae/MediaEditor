#pragma once

#include <QMainWindow>
#include "ui_fileuploadwindow.h"

class FileUploadWindow : public QMainWindow
{
	Q_OBJECT

public:
	FileUploadWindow(QWidget *parent = Q_NULLPTR);
	~FileUploadWindow();

private:
	Ui::FileUploadWindow ui;
};
