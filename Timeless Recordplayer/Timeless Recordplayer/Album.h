/// <summary>
/// by Elisabeth Sykorova
/// March 2024
/// </summary>

#pragma once
#include "SFML/Graphics.hpp" 
#include <iostream>


class Album
{
private:

	sf::Vector2f speed; // speed of the movement

public:
	Album();
	void setupCover(int index);
	void moveUp();
	void moveDown();

	sf::Vector2f m_firstPoint; // position of the first point of the cover

	sf::RectangleShape m_cover;
	sf::Sprite m_coverSprite;

	float m_coverSideSize = 250.0f; // size of the album's side
	sf::Vector2f m_coverPosition; // position of the album

	bool m_revealAlbum = false; // if album is revealed
	int m_revealedBy = 0; // counter by how much it is revealed

	sf::Texture m_albumsTexture; // texture (one spritesheet for all)

	const int MAX_REVEAL_BY = 30; // constant for how much the album reveals

};
