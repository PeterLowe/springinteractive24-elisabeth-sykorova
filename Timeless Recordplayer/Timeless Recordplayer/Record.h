#pragma once

#include "SFML/Graphics.hpp" 
#include <iostream>

class Record
{

public:
	sf::CircleShape vinyl;
	void setup();
	void moveRight();
	sf::Vector2f speed;
	sf::Vector2f currentPosition;

	float vinylRadius = 100;




};




