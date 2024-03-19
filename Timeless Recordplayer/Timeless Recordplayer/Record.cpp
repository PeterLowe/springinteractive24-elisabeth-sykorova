#include "Record.h"

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

void Record::moveRight()
{
	speed = { 5.0f,0.0f };
	vinylPosition += speed;
	vinyl.setPosition(vinylPosition);
	m_vinylSprite.setPosition(vinylPosition);

}

void Record::moveLeft()
{
	speed = { -5.0f,0.0f };
	vinyl.setPosition(vinyl.getPosition() + speed);
	m_vinylSprite.setPosition(vinyl.getPosition() + speed);

}

void Record::followMouse(sf::Vector2f t_mousePosition)
{
	vinyl.setPosition(t_mousePosition);
	m_vinylSprite.setPosition(t_mousePosition);
}

void Record::fadeOut()
{
	spriteColor.a -= 255 / MAX_REVEAL_BY;
	m_vinylSprite.setColor(spriteColor);
}


