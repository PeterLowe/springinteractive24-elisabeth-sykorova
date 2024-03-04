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

	// shape A,B,C,D
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
