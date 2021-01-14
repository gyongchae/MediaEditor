#pragma once
#include "qsfmlcanvas.h"
#include <QMouseEvent>
#include <memory>

#ifdef max
#undef max
#undef min
#endif

typedef struct texSprite
{
	sf::Texture tx;
	sf::Sprite sp;
	int nIndex;
}TEXSPRITE,*LPTEXSPRITE;

class QTextAligner : public QSFMLCanvas
{
	Q_OBJECT

public:
	enum previewtype {DEFAULT, TEXT, BITMAP, IMAGELIST};
	QTextAligner(QWidget* parent, const QPoint& position, const QSize& size);
	QTextAligner(QWidget* parent, const QPoint& position, const QSize& size, previewtype type);
	virtual ~QTextAligner(void);

private :
	void OnInit();
    void OnUpdate();
	void OnResize(int x,int y);
	void mouseMoveEvent ( QMouseEvent * event );
	void mousePressEvent ( QMouseEvent * event );
	void mouseReleaseEvent ( QMouseEvent * event );

public:
	void clearAllSprite();
	void setTexSprite(int nIndex,int nWidth,int nHeight,int nXPos,int nYPos,void* pVoid);
	void removeIndex(int nIndex);

	std::vector<std::shared_ptr<sf::Texture>> m_vTexture;
	std::vector<std::shared_ptr<sf::Sprite>> m_vSprite;
	std::map<int,std::shared_ptr<TEXSPRITE>> m_mTexSprite;

	bool m_bSelected{ false };
	int nIndexed{ -1 };
	int nInitPosX{0};
	int nInitPosY{0};
	previewtype m_previewtype{ DEFAULT };

public:
	void setBackgroundColor(QColor &color);
	void setBorderColor(QColor &color);
	QColor backgroundColor() const;

private:
	QColor m_backColor;
	QColor m_borderColor;

signals:
	void posChanged(int /*nIndex*/,int /*x*/,int /*y*/);
	
};
