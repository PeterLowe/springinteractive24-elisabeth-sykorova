/// <summary>
/// by Elisabeth Sykorova
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "Album.h"
#include "Record.h"

const int ALBUM_NUM = 6;
const int REVEAL_BY = 20; // multiplied by speed in album

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	void setupFontAndText();
	void setupSprite();
	void processMouseMovement(sf::Event t_event);
	void processMousePressed(sf::Event t_event);
	void checkHovering(sf::CircleShape t_dot);
	//void setupAlbum(float t_firstPointX, float t_firstPointY);
	void reveal(int t_index);
	void hide(int t_index);

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game
	Album albums[ALBUM_NUM];
	int albumBeingRevealed = ALBUM_NUM + 1;
	int albumPreviouslyRevealed = ALBUM_NUM + 1;

	int albumScatterX = 15;
	int albumScatterY = 30;

	sf::Vector2f m_mouseEnd;
	sf::CircleShape m_mouseDot{1.0f};

	const static int TEXTURES_NUM = 2;
	sf::Texture m_purpleFoxTexture;
	sf::Texture m_fleetwoodTexture;

	sf::Texture textures[TEXTURES_NUM] = { m_purpleFoxTexture, m_fleetwoodTexture };


	bool revealing = false;


	Record recordOne;
	

};

#endif // !GAME_HPP

