#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "ui_qgleslcdcanvas.h"

class QGLESLCDCanvas : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	explicit QGLESLCDCanvas(QWidget *parent = Q_NULLPTR);
	virtual ~QGLESLCDCanvas();

private:
	Ui::QGLESLCDCanvas ui;
};
