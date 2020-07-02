#pragma once
#include <SFML/Graphics.hpp>
#include <QWidget>

///#pragma comment(lib,"sfml-main-d.lib")
#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#else
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-system.lib")
#endif
class QSFMLCanvas :
	public QWidget, public sf::RenderWindow
{
	Q_OBJECT

public:
	QSFMLCanvas(QWidget *parent, const QPoint& Position, const QSize& size);
	virtual ~QSFMLCanvas(void);

public:
	virtual void OnInit()=0;
    virtual void OnUpdate()=0;
	virtual void OnResize(int x, int y)=0;
    virtual QPaintEngine* paintEngine() const;
    virtual void showEvent(QShowEvent*);
    virtual void paintEvent(QPaintEvent*);
	virtual void resizeEvent(QResizeEvent *resizeEvent);

private:
    bool   m_bInitialized;
};
