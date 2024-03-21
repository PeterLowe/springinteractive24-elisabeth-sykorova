/// <summary>
/// by Elisabeth Sykorova
/// March 2024
/// </summary>

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

	sf::Vector2f speed; // speed of the record
	sf::Vector2f currentPosition; // location

	float vinylRadius = 97;
	sf::Vector2f vinylPosition;


	int revealedBy = 0; // counter by how much the record is revealed
	bool revealed = false; // when fully revealed
	bool reveal = false; // when in the state of revealing
	bool setupForRevealing = false; // changes once at the start of revealing (setting the position, opacity,..)
	bool setupForHiding = false;
	bool hide = false;

	sf::CircleShape vinyl; // circle

	// sprite
	sf::Texture m_vinylTexture; 
	sf::Sprite m_vinylSprite;

	sf::Color spriteColor = (sf::Color::White);

	const int MAX_REVEAL_BY = 20;


};




