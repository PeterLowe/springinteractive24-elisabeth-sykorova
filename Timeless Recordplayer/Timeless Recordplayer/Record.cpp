#include "Record.h"

void Record::setup()
{
	vinyl.setRadius(vinylRadius);
	vinyl.setOrigin(vinylRadius, vinylRadius); //  centre of circle
	vinyl.setPosition(300.0f,400.0f);
	vinyl.setFillColor(sf::Color::Black);

}

void Record::moveRight()
{
	speed = { 1.0f,0.0f };

}
