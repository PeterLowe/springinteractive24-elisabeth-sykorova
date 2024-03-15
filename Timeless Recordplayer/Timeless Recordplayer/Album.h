
#pragma once
#include "SFML/Graphics.hpp" 
#include <iostream>



class Album
{
private:

	sf::Vector2f speed;
	

public:
	Album();
	void setupCover(float t_firstX, float t_firstY);
	void moveUp();
	void moveDown();

	void reveal();
	void hide();

	sf::Vector2f m_firstPoint;

	sf::RectangleShape m_cover;

	float coverSideSize = 200.0f; // size of the album's size
	sf::Vector2f coverPosition;
	bool revealed = false;

	bool revealAlbum = false;
	int revealedBy = 0;


};
