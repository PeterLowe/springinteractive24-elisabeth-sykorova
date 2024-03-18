#include "Album.h"


Album::Album()
{

}


void Album::setupCover(int index)
{

	int red = (rand() % 256) + 1;
	int green = (rand() % 256) + 1;
	int blue = (rand() % 256) + 1;
	int opacity = 255;

	sf::Vector2f coverPosition = { 250.0f + (index * 10.0f), 500.0f - (index * 30.0f)};

	m_cover.setPosition(coverPosition);
	m_coverSprite.setPosition(300.0f, 300.0f);

	m_cover.setOrigin(m_coverSideSize, m_coverSideSize);
	m_coverSprite.setOrigin(m_coverSideSize, m_coverSideSize);

	m_cover.setFillColor(sf::Color(red, green, blue, opacity));
	m_cover.setSize(sf::Vector2f(m_coverSideSize, m_coverSideSize));

	// sprite

	if (!m_albumsTexture.loadFromFile("ASSETS\\IMAGES\\albums.png"))
	{
		std::cout << "problem loading albums" << std::endl;
	}

	m_coverSprite.setPosition(coverPosition);
	m_coverSprite.setTexture(m_albumsTexture);

	float firstX = static_cast<int>(m_coverSideSize) * index;
	float firstY = 0;
	float secondX = static_cast<int>(m_coverSideSize);
	float secondY = static_cast<int>(m_coverSideSize);

	m_coverSprite.setTextureRect(sf::IntRect(firstX, firstY, secondX, secondY));
}


// moves all the points up by 1 pixel
void Album::moveUp()
{
	speed = { 0.0f, -3.0f };
	m_coverPosition = m_cover.getPosition() + speed;
	m_cover.setPosition(m_coverPosition);
	m_coverSprite.setPosition(m_coverPosition);

}

void Album::moveDown()
{
	speed = { 0.0f, 3.0f };
	m_coverPosition = m_cover.getPosition() + speed;
	m_cover.setPosition(m_coverPosition);
	m_coverSprite.setPosition(m_coverPosition);

}




