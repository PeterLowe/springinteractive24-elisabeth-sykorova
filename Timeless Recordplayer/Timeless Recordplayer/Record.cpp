/// <summary>
/// by Elisabeth Sykorova
/// March 2024
/// </summary>

#include "Record.h"


/// <summary>
/// setup record
/// </summary>
void Record::setup()
{

	if (!m_vinylTexture.loadFromFile("ASSETS\\IMAGES\\vinyl.png"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}


	vinyl.setRadius(vinylRadius);

	vinyl.setOrigin(vinylRadius, vinylRadius); //  centre of circle
	m_vinylSprite.setOrigin(vinylRadius, vinylRadius);

	vinyl.setPosition(vinylPosition);
	m_vinylSprite.setPosition(vinylPosition);

	m_vinylSprite.setTexture(m_vinylTexture);
	m_vinylSprite.setColor(spriteColor);
	vinyl.setFillColor(sf::Color::Black);

}

/// <summary>
/// moves right
/// </summary>
void Record::moveRight()
{
	speed = { 7.0f,0.0f };
	vinylPosition += speed;
	vinyl.setPosition(vinylPosition);
	m_vinylSprite.setPosition(vinylPosition);

}

/// <summary>
/// moves left
/// </summary>
void Record::moveLeft()
{
	speed = { -7.0f,0.0f };
	vinyl.setPosition(vinyl.getPosition() + speed);
	m_vinylSprite.setPosition(vinyl.getPosition() + speed);

}

/// <summary>
/// changes position to position of mouse cursor
/// </summary>
void Record::followMouse(sf::Vector2f t_mousePosition)
{
	vinyl.setPosition(t_mousePosition);
	m_vinylSprite.setPosition(t_mousePosition);
}

/// <summary>
/// lowers opacity
/// </summary>
void Record::fadeOut()
{
	spriteColor.a -= 255 / MAX_REVEAL_BY;
	m_vinylSprite.setColor(spriteColor);
}


