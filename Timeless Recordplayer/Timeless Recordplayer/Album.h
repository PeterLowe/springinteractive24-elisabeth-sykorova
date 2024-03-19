
#pragma once
#include "SFML/Graphics.hpp" 
#include <iostream>


class Album
{
private:

	sf::Vector2f speed;
	

public:
	Album();
	void setupCover(int index);
	void moveUp();
	void moveDown();

	sf::Vector2f m_firstPoint;

	sf::RectangleShape m_cover;
	sf::Sprite m_coverSprite;

	float m_coverSideSize = 250.0f; // size of the album's side
	sf::Vector2f m_coverPosition;

	bool m_revealAlbum = false;
	int m_revealedBy = 0;


	sf::Texture m_albumsTexture;

	const int MAX_REVEAL_BY = 30;

};
