#include "Album.h"


Album::Album()
{

}


void Album::setupCover(int index)
{

	/*int red = (rand() % 256) + 1; int green = (rand() % 256) + 1;
	int blue = (rand() % 256) + 1; int opacity = 255;*/ // debug

	sf::Vector2f coverPosition = { 350.0f - (index * 13.0f), 520.0f - (index * 34.0f)}; // first pos is {350.0f, 520.0f}, magic pos i decided to be the one

	// setup
	m_cover.setPosition(coverPosition);
	m_coverSprite.setPosition(300.0f, 300.0f);

	m_cover.setOrigin(m_coverSideSize, m_coverSideSize);
	m_coverSprite.setOrigin(m_coverSideSize, m_coverSideSize);

	//m_cover.setFillColor(sf::Color(red, green, blue, opacity)); //debug
	m_cover.setSize(sf::Vector2f(m_coverSideSize, m_coverSideSize));

	// sprite, texture
	if (!m_albumsTexture.loadFromFile("ASSETS\\IMAGES\\albums.png"))
	{
		std::cout << "problem loading albums" << std::endl;
	}

	m_coverSprite.setPosition(coverPosition);
	m_coverSprite.setTexture(m_albumsTexture);


	// points for texture rectangle (one spritesheet for all covers)
	float firstX = static_cast<int>(m_coverSideSize) * index;
	float firstY = 0;
	float secondX = static_cast<int>(m_coverSideSize);
	float secondY = static_cast<int>(m_coverSideSize);

	m_coverSprite.setTextureRect(sf::IntRect(firstX, firstY, secondX, secondY));
}

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




