
#pragma once
#include "SFML/Graphics.hpp" 
#include <iostream>



class Album
{
public:
	Album();
	void setup(float t_firstX, float t_firstY);
	void moveUp();
	void moveDown();

	// album cover - later seperate class
	sf::ConvexShape m_angledAlbum;
	int m_pointCount{ 4 };
	bool m_revealed = false;
	int m_movedUpCount = 0;
	int m_movedDownCount = 0;

	const int REVEAL_BY = 80; // SHOULD BE GLOBAL ACROSS WHOLE PROJ

};
