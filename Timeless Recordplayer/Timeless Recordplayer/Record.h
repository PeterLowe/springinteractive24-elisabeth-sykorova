#pragma once

#include "SFML/Graphics.hpp" 
#include <iostream>

class Record
{

public:
	sf::CircleShape vinyl;
	void setup();
	void moveRight();
	void moveLeft();
	void moveUp(sf::Vector2f t_startingPosition);
	void followMouse(sf::Vector2f t_mousePosition);

	sf::Vector2f speed;
	sf::Vector2f currentPosition;

	float vinylRadius = 90;
	sf::Vector2f vinylPosition{0.0f, 0.0f};

	bool revealed = false;

	int revealedBy = 0;
	bool reveal = false;
	bool setupForRevealing = false;
	bool hide = false;

	sf::Color color = (sf::Color::Black);


};




