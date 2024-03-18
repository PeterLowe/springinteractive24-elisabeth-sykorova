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
#include <SFML/Audio.hpp>
#include "Album.h"
#include "Record.h"

const int ALBUM_NUM = 6;
const int REVEAL_BY = 30; // multiplied by speed in album

const int NORTH = 1;
const int SOUTH = 2;
const int EAST = 3;
const int WEST = 4;

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
	void processMouseMovement(sf::Event t_event);
	//void setupAlbum(float t_firstPointX, float t_firstPointY);
	void setupRecordPlayer();


	void processMouseWheel(sf::Event t_event);
	void processMousePressed(sf::Event t_event);

	void checkVinylPlayerCollision();

	void setupMusic();
	sf::Sound songs[ALBUM_NUM];
	sf::Texture textures[ALBUM_NUM];


	sf::RectangleShape square;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game


	Album albums[ALBUM_NUM];
	Record record;

	sf::Vector2i m_mouseEnd;
	sf::Vector2f m_mouseEndVector;
	sf::CircleShape m_mouseDot{1.0f};


	

	int m_albumToReveal = -1;
	//int m_albumRevealed = -1;
	bool m_getVinyl = false;
	bool m_holdingVinyl = false;

	bool m_mouseReleased = true;
	bool m_mouseOnVinyl = false;


	sf::RectangleShape m_recordPlayer;


	//songs
	// Everblue Forest - Purple Fox Town
	sf::SoundBuffer m_purpleFoxTownBuffer;
	sf::Sound m_purpleFoxTown;

	// Mutter - Rammstein
	sf::SoundBuffer m_rammsteinBuffer;
	sf::Sound m_rammstein;

	bool m_songPlaying = false;

	bool hidingSet = true;

	const int MAX_REVEALED_BY = 30;


	

};

#endif // !GAME_HPP

