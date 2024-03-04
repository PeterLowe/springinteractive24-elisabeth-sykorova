
#pragma once
#include "SFML/Graphics.hpp" 
#include <iostream>


class Album
{
public:
	Album();
	void setup(float t_firstX, float t_firstY);

	// album cover - later seperate class
	sf::ConvexShape m_angledAlbum;
	int m_pointCount{ 4 };
};
