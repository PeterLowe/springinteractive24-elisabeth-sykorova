
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

	float m_coverSideSize = 220.0f; // size of the album's side
	sf::Vector2f m_coverPosition;
	bool m_revealed = false;

	bool m_revealAlbum = false;
	int m_revealedBy = 0;

	static const int ALBUM_NUM = 6;

	sf::Texture m_albumsTexture;

};
