/// <summary>
/// by Elisabeth Sykorova
/// March 2024
/// </summary>

#include "Album.h"


Album::Album()
{

}

/// <summary>
/// sets up the cover
/// </summary>
void Album::setupCover(int index)
{

	sf::Vector2f coverPosition = { 350.0f - (index * 13.0f), 520.0f - (index * 34.0f) };
	// first pos is {350.0f, 520.0f}, magic pos i decided to be the one
	// 13.0f is x offset, 34.0f is y offset (the way they are stacked one after the other)

	m_cover.setPosition(coverPosition);

	m_cover.setOrigin(m_coverSideSize, m_coverSideSize);
	m_coverSprite.setOrigin(m_coverSideSize, m_coverSideSize);

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

/// <summary>
/// moves the album up
/// </summary>
void Album::moveUp()
{
	speed = { 0.0f, -3.0f };
	m_coverPosition = m_cover.getPosition() + speed;

	m_cover.setPosition(m_coverPosition);
	m_coverSprite.setPosition(m_coverPosition);

}

/// <summary>
/// moves the album down
/// </summary>
void Album::moveDown()
{
	speed = { 0.0f, 3.0f };
	m_coverPosition = m_cover.getPosition() + speed;

	m_cover.setPosition(m_coverPosition);
	m_coverSprite.setPosition(m_coverPosition);

}




