#include "Album.h"


Album::Album()
{

}


void Album::setupCover(float t_firstX, float t_firstY)
{

	int red = (rand() % 256) + 1;
	int green = (rand() % 256) + 1;
	int blue = (rand() % 256) + 1;
	int opacity = 255;

	sf::Vector2f coverPosition = { t_firstX, t_firstY };

	m_cover.setPosition(coverPosition);
	m_cover.setOrigin(coverSideSize, coverSideSize);
	m_cover.setFillColor(sf::Color(red, green, blue, opacity));
	m_cover.setSize(sf::Vector2f(coverSideSize, coverSideSize));



}

// moves all the points up by 1 pixel
void Album::moveUp()
{
	speed = { 0.0f, -1.0f };
	coverPosition = m_cover.getPosition() + speed;
	m_cover.setPosition(coverPosition);

}

void Album::moveDown()
{
	speed = { 0.0f, 1.0f };
	coverPosition = m_cover.getPosition() + speed;
	m_cover.setPosition(coverPosition);

}

void Album::reveal()
{
	for (int revealBy = 50; revealBy > 0; revealBy--)
	{
		moveUp();
	}
	revealed = true;
}

void Album::hide()
{
	for (int hideBy = 50; hideBy > 0; hideBy--)
	{
		moveDown();
	}
	revealed = false;

}


