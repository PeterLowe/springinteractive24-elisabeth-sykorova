#pragma once

#include "SFML/Graphics.hpp" 
#include <iostream>

class Record
{

public:
	void setup();
	void moveRight();
	void moveLeft();
	void fadeOut();
	void followMouse(sf::Vector2f t_mousePosition);

	sf::Vector2f speed;
	sf::Vector2f currentPosition;

	float vinylRadius = 97;
	sf::Vector2f vinylPosition;


	int revealedBy = 0;
	bool revealed = false; // when fully revealed
	bool reveal = false; // when in the state of revealing
	bool setupForRevealing = false; // changes once at the start of revealing (setting the position, opacity,..)
	bool hide = false;


	sf::CircleShape vinyl; // circle

	sf::Texture m_vinylTexture; 
	sf::Sprite m_vinylSprite;

	sf::Color color = (sf::Color::Black);
	sf::Color spriteColor = (sf::Color::White);

	const int MAX_REVEAL_BY = 20;


};




