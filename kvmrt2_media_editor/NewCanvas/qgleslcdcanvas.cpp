#include "qgleslcdcanvas.h"

QGLESLCDCanvas::QGLESLCDCanvas(QWidget *parent)
	: QOpenGLWidget(parent)
{
	ui.setupUi(this);
}

QGLESLCDCanvas::~QGLESLCDCanvas()
{
}
