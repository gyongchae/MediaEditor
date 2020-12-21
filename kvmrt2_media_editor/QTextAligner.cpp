#include "QTextAligner.h"
#include <tchar.h>
#include <qdebug.h>

QTextAligner::QTextAligner(QWidget *parent, const QPoint& position, const QSize& size)
	:QSFMLCanvas(parent, position, size)
{

}

QTextAligner::QTextAligner(QWidget * parent, const QPoint & position, const QSize & size, previewtype type) : QSFMLCanvas(parent, position, size)
{
	m_previewtype = type;
	m_backColor = QColor(192, 192, 192); // init color : gray
	m_borderColor = QColor(0, 255, 0); // init color : green
}

QTextAligner::~QTextAligner(void)
{
}

void QTextAligner::OnInit()
{
}

void QTextAligner::OnUpdate()
{
	int r = m_borderColor.red(); 
	int g = m_borderColor.green();
	int b = m_borderColor.blue();

	clear(sf::Color(m_backColor.red(), m_backColor.green(), m_backColor.blue(), m_backColor.alpha())); // 배경색

	sf::Vector2u vSize = getSize();
	sf::Vertex quads[] =
	{
		// 전체 배경 테두리 세팅, jkc
		sf::Vertex(sf::Vector2f(1,1),				sf::Color(r,g,b)),
		sf::Vertex(sf::Vector2f(vSize.x,1),			sf::Color(r,g,b)),
		sf::Vertex(sf::Vector2f(vSize.x,vSize.y),	sf::Color(r,g,b)),
		sf::Vertex(sf::Vector2f(1,vSize.y),			sf::Color(r,g,b)),
		sf::Vertex(sf::Vector2f(1,1),				sf::Color(r,g,b)),
	};
	if (m_previewtype != IMAGELIST)
	{
		// 전체 배경 테두리 그리기
		//draw(quads, 5, sf::LineStrip);
	}

	sf::FloatRect tRect;
	std::map<int, std::shared_ptr<TEXSPRITE>>::iterator nit;
	for (nit = m_mTexSprite.begin(); nit != m_mTexSprite.end(); nit++)
	{
		// 아이템 자체 그리기
		draw(nit->second.get()->sp);
		
		// 아이템 테두리 세팅
		tRect = nit->second.get()->sp.getGlobalBounds();
		quads[0].position.x = tRect.left;
		quads[0].position.y = tRect.top;

		quads[1].position.x = tRect.left + tRect.width;
		quads[1].position.y = tRect.top;

		quads[2].position.x = tRect.left + tRect.width;;
		quads[2].position.y = tRect.top + tRect.height;;

		quads[3].position.x = tRect.left;
		quads[3].position.y = tRect.top + tRect.height;

		quads[4].position.x = tRect.left;
		quads[4].position.y = tRect.top;
		
		if (m_previewtype != IMAGELIST)
		{
			// 아이템 테두리 그리기
			//draw(quads, 5, sf::LineStrip);
		}
	}
}

void QTextAligner::OnResize(int x, int y)
{
	qDebug() << "SFML view resize:" << x << y;
	setSize(sf::Vector2u(x, y));
	setView(sf::View(sf::FloatRect(0.f, 0.f, (float)x, (float)y)));
}

void QTextAligner::mouseMoveEvent(QMouseEvent * event)
{
	if (m_previewtype == IMAGELIST)
	{
		int nX, nY;
		if (m_bSelected && (nIndexed > -1))
		{
			nX = event->pos().x() - nInitPosX;
			nY = event->pos().y() - nInitPosY;

			std::map<int, std::shared_ptr<TEXSPRITE>>::iterator nit;
			nit = m_mTexSprite.find(nIndexed);
			if (nit != m_mTexSprite.end())
			{
				nit->second.get()->sp.move((float)nX, (float)nY);
				sf::Vector2f pos = nit->second.get()->sp.getPosition();
				emit posChanged(nit->second.get()->nIndex, (int)pos.x, (int)pos.y);
				nInitPosX = event->pos().x();
				nInitPosY = event->pos().y();
			}
		}
		update();
	}
}

void QTextAligner::mousePressEvent(QMouseEvent * event)
{
	if (m_previewtype == IMAGELIST)
	{
		int nX = event->pos().x();
		int nY = event->pos().y();

		std::map<int, std::shared_ptr<TEXSPRITE>>::iterator nit;

		for (nit = m_mTexSprite.begin(); nit != m_mTexSprite.end(); nit++)
		{
			sf::Rect<float> tRect = nit->second.get()->sp.getGlobalBounds();
			if (tRect.contains(nX, nY))
			{
				m_bSelected = true;
				nIndexed = nit->first;
			}
		}

		nInitPosX = nX;
		nInitPosY = nY;
	}
}
void QTextAligner::mouseReleaseEvent(QMouseEvent * event)
{
	if (m_previewtype == IMAGELIST)
	{
		m_bSelected = false;
		nIndexed = -1;
	}
}

void QTextAligner::clearAllSprite()
{
	m_mTexSprite.clear();
}

void QTextAligner::setTexSprite(int nIndex, int nWidth, int nHeight, int nXPos, int nYPos, void* pVoid)
{
	std::shared_ptr<TEXSPRITE> pTemp = std::shared_ptr<TEXSPRITE>(new TEXSPRITE);

	pTemp.get()->nIndex = nIndex;
	pTemp.get()->tx.create(nWidth, nHeight);
	pTemp.get()->tx.update((sf::Uint8*)pVoid);
	pTemp.get()->tx.setSmooth(true);

	pTemp.get()->sp.setTexture(pTemp.get()->tx, true);
	pTemp.get()->sp.move((float)nXPos, (float)nYPos);

	m_mTexSprite[nIndex] = pTemp;
}

void QTextAligner::removeIndex(int nIndex)
{
	m_mTexSprite.erase(nIndex);
}

void QTextAligner::setBackgroundColor(QColor & color)
{
	m_backColor = color;
}

void QTextAligner::setBorderColor(QColor & color)
{
	m_borderColor = color;
}

QColor QTextAligner::backgroundColor() const
{
	return m_backColor;
}