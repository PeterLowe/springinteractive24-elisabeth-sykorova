
#pragma once
#include "SFML/Graphics.hpp" 
#include <iostream>



class Album
{
private:
	int m_pointCount{ 4 };
	bool m_revealed = false;
	sf::Vector2f speed;
	

public:
	Album();
	void setup(float t_firstX, float t_firstY);
	void moveUp();
	void moveDown();

	sf::VertexArray m_cover {sf::Quads, 4};
	sf::Texture m_fleetwoodTexture;
	sf::Texture m_albumTexture;


};
