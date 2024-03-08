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
	// texture

}

void Album::setupQuadAlbum()
{
	int sideSize = 210; // x, size of album (x^2)
	sf::Vector2f firstPoint = { 50.0f, 250.0f }; // coordinates of top left point
	int angleBy = 20; // tilt in y axis
	

	//m_quadAlbum[0].position = { 50.0f, 200.0f };
	//m_quadAlbum[0].texCoords = { 50.0f,200.0f };

	
	// texture

	if (!m_albumTexture.loadFromFile("ASSETS\\IMAGES\\purpleFoxTown.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading cover" << std::endl;
	}


}

// moves all the points up by 1 pixel
void Album::moveUp()
{
	speed = { 0.0f, -0.25f };

	m_angledAlbum.move(speed);
}

void Album::moveDown()
{
	speed = { 0.0f, 0.25f };

	m_angledAlbum.move(speed);

}

bool Album::revealed()
{
	return m_revealed;
}

void Album::setRevealed(bool t_isRevealed)
{
	m_revealed = t_isRevealed;
}


