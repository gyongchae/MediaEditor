#include "QSFMLCanvas.h"
#include <qdebug.h>


QSFMLCanvas::QSFMLCanvas(QWidget* pParent, const QPoint& Position, const QSize& Size) 
:QWidget(pParent),m_bInitialized(false)
{
    // Setup some states to allow direct rendering into the widget
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    // Set strong focus to enable keyboard events to be received
    setFocusPolicy(Qt::StrongFocus);

    // Setup the widget geometry
    move(Position);
    resize(Size);

    // Setup the timer
}

QSFMLCanvas::~QSFMLCanvas(void)
{
}

QPaintEngine* QSFMLCanvas::paintEngine() const
{
    return 0;
}

void QSFMLCanvas::showEvent(QShowEvent*)
{
    if (!m_bInitialized)
    {
        // Create the SFML window with the widget handle
		RenderWindow::create((HWND)winId());
		
        // Let the derived class do its specific stuff
        OnInit();

        // Setup the timer to trigger a refresh at specified framerate
        //connect(&myTimer, SIGNAL(timeout()), this, SLOT(repaint()));
        //myTimer.start();

        m_bInitialized = true;
    }
}

void QSFMLCanvas::resizeEvent(QResizeEvent *resizeEvent)
{
	OnResize(size().width(),size().height());
}

void QSFMLCanvas::paintEvent(QPaintEvent*)
{
    // Let the derived class do its specific stuff
    OnUpdate();

    // Display on screen
    display();
}



