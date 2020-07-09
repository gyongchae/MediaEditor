#include "qgleslcdcanvas.h"
#include <qdebug.h>
#include <qtimer.h>
#include <qevent.h>

QGLESLCDCanvas::QGLESLCDCanvas(QWidget *parent)
	: QOpenGLWidget(parent)
{
	ui.setupUi(this);
}

QGLESLCDCanvas::~QGLESLCDCanvas()
{

}

void QGLESLCDCanvas::initializeGL()
{
	qDebug() << Q_FUNC_INFO;
	initializeOpenGLFunctions(); // must be called first!
	glClearColor(0, 0, 0, 1); // init background color
	initShader();
}

void QGLESLCDCanvas::resizeGL(int w, int h)
{
	qDebug() << Q_FUNC_INFO << w << h;
	m_w = w;
	m_h = h;
}

void QGLESLCDCanvas::paintGL()
{
	qDebug() << Q_FUNC_INFO;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, m_w, m_h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.7f, 0.4f, 0.0f, 0.0f);

	if (!program.bind())
		close();
}

void QGLESLCDCanvas::mouseMoveEvent(QMouseEvent * e)
{
	qDebug() << Q_FUNC_INFO << e->globalPos() << e->localPos();
}

void QGLESLCDCanvas::mousePressEvent(QMouseEvent * e)
{
	qDebug() << Q_FUNC_INFO << e->globalPos() << e->localPos();
}

void QGLESLCDCanvas::mouseReleaseEvent(QMouseEvent * e)
{
	qDebug() << Q_FUNC_INFO << e->globalPos() << e->localPos();
}

void QGLESLCDCanvas::dragMoveEvent(QDragMoveEvent * e)
{
	qDebug() << Q_FUNC_INFO << e->isAccepted();
}

void QGLESLCDCanvas::dragEnterEvent(QDragEnterEvent * e)
{
	qDebug() << Q_FUNC_INFO << e->isAccepted();
}

void QGLESLCDCanvas::contextMenuEvent(QContextMenuEvent * e)
{
	qDebug() << Q_FUNC_INFO << e->isAccepted();
}

void QGLESLCDCanvas::dropEvent(QDropEvent * e)
{
	qDebug() << Q_FUNC_INFO << e->isAccepted();
}

void QGLESLCDCanvas::initShader()
{
	const char vShaderStr[] =
		"attribute vec4 a_position;\n"
		"attribute vec2 a_texcoord;\n"
		"varying vec2 v_texcoord;\n"
		"uniform mat4 u_matrix;\n"
		"void main()\n"
		"{\n"
		"gl_Position = u_matrix * a_position;\n"
		"v_texcoord = a_texcoord;\n"
		"}\n";

	const char fShaderStr[] =
		"varying vec2 v_texcoord;\n"
		"uniform vec4 u_color;\n"
		"uniform sampler2D firstTex;\n"
		"void main()\n"
		"{\n"
		"gl_FragColor =  texture2D(firstTex, v_texcoord)*u_color;\n"
		"}\n";

	if (!program.addShaderFromSourceCode(QOpenGLShader::Vertex, vShaderStr))
	{
		qDebug() << Q_FUNC_INFO << "vertex error";
		close();
	}

	// Compile fragment shader
	if (!program.addShaderFromSourceCode(QOpenGLShader::Fragment, fShaderStr))
	{
		qDebug() << Q_FUNC_INFO << "frag error!";
		close();
	}

	// Link shader pipeline
	if (!program.link())
	{
		qDebug() << Q_FUNC_INFO << "link error!";
		close();
	}

	m_uPosScrLoc = program.attributeLocation("a_position");
	m_uTexCoordScrLoc = program.attributeLocation("a_texcoord");
	m_uMatrixLoc = program.uniformLocation("u_matrix");
	m_nFirstTex = program.uniformLocation("firstTex");
	m_uColorLoc = program.uniformLocation("u_color");
}
