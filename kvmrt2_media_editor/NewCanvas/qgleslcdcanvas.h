#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "ui_qgleslcdcanvas.h"

class QGLESLCDCanvas : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT
private:
	Ui::QGLESLCDCanvas ui;

public:
	explicit QGLESLCDCanvas(QWidget *parent = Q_NULLPTR);
	virtual ~QGLESLCDCanvas();
	
	// qopenglwidget's override func
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;

	// override func
public:
	void mouseMoveEvent(QMouseEvent *e) override;
	void mousePressEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;
	void dragMoveEvent(QDragMoveEvent * e) override;
	void dragEnterEvent(QDragEnterEvent * e) override;
	void contextMenuEvent(QContextMenuEvent * e) override;
	void dropEvent(QDropEvent * e) override;

	// func called in initializeGL()
public:
	void initShader();

private:
	GLuint m_uPosScrLoc;
	GLuint m_uTexCoordScrLoc;
	GLuint m_uMatrixLoc;
	GLuint m_uColorLoc;
	GLint m_nFirstTex;
	QOpenGLShaderProgram program;

private:
	int m_w{0};
	int m_h{0};
};
