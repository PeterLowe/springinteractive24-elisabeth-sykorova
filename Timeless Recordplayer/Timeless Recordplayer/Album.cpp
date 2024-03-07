#include "Album.h"


Album::Album()
{

}

void Album::setup(float t_firstX, float t_firstY)
{
	int sideSize = 210; // x, size of album (x^2)
	sf::Vector2f firstPoint = { t_firstX, t_firstY }; // coordinates of top left point
	int angleBy = 20; // tilt in y axis

	m_angledAlbum.setPointCount(m_pointCount);

	// shape A,B,C,D - points set that they are relevant to the first point that's passed
	// note: angled, so side |AB| should be shorter from this pov
	m_angledAlbum.setPoint(0, sf::Vector2f(firstPoint)); // A
	m_angledAlbum.setPoint(1, sf::Vector2f((firstPoint.x + sideSize), (firstPoint.y + angleBy))); // B
	m_angledAlbum.setPoint(2, sf::Vector2f((firstPoint.x + sideSize), (firstPoint.y + sideSize + angleBy))); // C
	m_angledAlbum.setPoint(3, sf::Vector2f(firstPoint.x, (firstPoint.y + sideSize))); // D

	int red = (rand() % 256) + 1;
	int green = (rand() % 256) + 1;
	int blue = (rand() % 256) + 1;
	int opacity = 255;


	m_angledAlbum.setFillColor(sf::Color(red, green, blue, opacity));
}

// moves all the points up by 1 pixel
void Album::moveUp()
{
	speed = { 0.0f, -0.25f };

	if (m_revealed != true)
	{
		for (int point = 0; point < m_pointCount; point++)
		{
			sf::Vector2f albumPoint = m_angledAlbum.getPoint(point);
			albumPoint += speed;
			m_angledAlbum.setPoint(point, albumPoint);
		}
	}


}

void Album::moveDown()
{
	speed = { 0.0f, 0.25f };


	if (m_revealed != false)
	{
		for (int point = 0; point < m_pointCount; point++)
		{
			sf::Vector2f albumPoint = m_angledAlbum.getPoint(point);
			albumPoint += speed;
			m_angledAlbum.setPoint(point, albumPoint);
		}
	}

}

bool Album::revealed()
{
	return m_revealed;
}

void Album::setRevealed(bool t_isRevealed)
{
	m_revealed = t_isRevealed;
}


