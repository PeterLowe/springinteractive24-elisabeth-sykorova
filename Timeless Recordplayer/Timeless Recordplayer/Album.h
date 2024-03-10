
#pragma once
#include "SFML/Graphics.hpp" 
#include <iostream>



class Album
{
private:
	int m_pointCount{ 4 };
	bool m_revealed = false;
	int m_movedUpCount = 0;
	int m_movedDownCount = 0;
	sf::Vector2f speed;
	

public:
	Album();
	void setup(float t_firstX, float t_firstY);
	void setupQuadAlbum(float t_firstX, float t_firstY);
	void moveUp();
	void moveDown();
	bool revealed();
	void setRevealed(bool t_isRevealed);
	sf::ConvexShape m_angledAlbum;
	sf::VertexArray m_quadAlbum {sf::Quads, 4};
	sf::Texture m_albumTexture;


};
