#include "Record.h"

void Record::setup()
{
	vinyl.setRadius(vinylRadius);
	vinyl.setOrigin(vinylRadius, vinylRadius); //  centre of circle
	vinyl.setPosition(vinylPosition);
	vinyl.setFillColor(sf::Color::Black);

}

void Record::moveRight()
{
	speed = { 5.0f,0.0f };
	vinylPosition += speed;
	vinyl.setPosition(vinylPosition);
	//revealed = true;
}

void Record::moveLeft()
{
	speed = { -5.0f,0.0f };
	vinyl.setPosition(vinyl.getPosition() + speed);
	//revealed = true;
}

void Record::followMouse(sf::Vector2f t_mousePosition)
{
	vinyl.setPosition(t_mousePosition);

}

void Record::moveUp(sf::Vector2f t_startingPosition)
{
	vinylPosition.x = t_startingPosition.x;
	vinylPosition.y = t_startingPosition.y - 100.0f;
	speed = { 0.0f,-120.0f };
	vinylPosition += speed;
	vinyl.setPosition(vinylPosition);
	//revealed = true;
}

