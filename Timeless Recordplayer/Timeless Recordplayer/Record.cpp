#include "Record.h"

void Record::setup()
{
	vinyl.setRadius(vinylRadius);
	vinyl.setOrigin(vinylRadius, vinylRadius); //  centre of circle
	vinyl.setPosition(vinylPosition);
	vinyl.setFillColor(sf::Color::Black);

}

void Record::moveRight(sf::Vector2f t_startingPosition)
{
	vinylPosition.x = t_startingPosition.x;
	vinylPosition.y = t_startingPosition.y - 100.0f;
	speed = { 100.0f,0.0f };
	vinylPosition += speed;
	vinyl.setPosition(vinylPosition);
}

void Record::followMouse(sf::Vector2f t_mousePosition)
{
	vinyl.setPosition(t_mousePosition);

}

