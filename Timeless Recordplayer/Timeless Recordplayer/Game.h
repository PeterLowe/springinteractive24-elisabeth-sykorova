/// <summary>
/// by Elisabeth Sykorova
/// March 2024
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

const int ALBUM_NUM = 6; // number of albums in the program

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
	// base
	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	// setups
	void setupFontAndText();
	void setupMusic();
	void setupBackground();
	void setupBox();
	void setupRecordPlayer();
	void animateRecordplayer();

	// mouse events
	void processMouseMovement(sf::Event t_event);
	void processMouseWheel(sf::Event t_event);
	void processMousePressed(sf::Event t_event);
	void processMouseReleased(sf::Event t_event);

	// collisions
	void checkVinylPlayerCollision();
	void checkVinylAlbumCollision();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_font; // font used by message
	sf::Text m_instructions; // text used for instructions on screen
	sf::Text m_songTitle; // title of the song playing
	bool m_exitGame; // control exiting game


	Album albums[ALBUM_NUM];
	Record record; 

	sf::Vector2i m_mouseEnd; // gets the coordinates of the end of the mouse
	sf::Vector2f m_mouseEndVector; // converts to vector
	sf::CircleShape m_mouseDot{1.0f}; // used to check collisions

	static constexpr int NO_ALBUM_REVEALED = -1; // magical constant for no album revealed
	int m_albumRevealed = NO_ALBUM_REVEALED; // tracking the album currently revealed
	bool m_holdingVinyl = false; // if the vinyl is held

	bool m_mouseReleased = true; // if mouse is released or not
	bool m_mouseOnVinyl = false; // if mouse is collided with vinyl
	bool m_vinylDropped = false; // if mouse is placed onto the record player
	bool m_showInstructions = true; // toggle show instructions

	// record player
	sf::RectangleShape m_recordPlayer;
	sf::Sprite m_recordPlayerSprite;
	sf::Texture m_recordPlayerTexture;
	sf::Texture m_recordplayerActive1;
	sf::Texture m_recordplayerActive2;

	// vinyl box
	// front
	sf::Sprite m_boxFrontSprite;
	sf::Texture m_boxFrontTexture;
	//back
	sf::Sprite m_boxBackSprite;
	sf::Texture m_boxBackTexture;

	// background
	sf::Sprite m_backgroundSprite;
	sf::Texture m_backgroundTexture;


	//songs
	// Everblue Forest - Purple Fox Town
	sf::SoundBuffer m_purpleFoxTownBuffer;
	sf::Sound m_purpleFoxTown;

	// Custer - Slipknot
	sf::SoundBuffer m_slipknotBuffer;
	sf::Sound m_slipknot;

	// Ivan Trojan - Vypsana fixa
	sf::SoundBuffer m_vypsanaFixaBuffer;
	sf::Sound m_vypsanaFixa;

	// Enjoy the Silence - Depeche Mode
	sf::SoundBuffer m_depecheBuffer;
	sf::Sound m_depeche;

	// End of the Beginning - DJO
	sf::SoundBuffer m_djoBuffer;
	sf::Sound m_djo;

	// Kiss the Go-Goat - Ghost
	sf::SoundBuffer m_ghostBuffer;
	sf::Sound m_ghost;

	// array for songs
	sf::Sound songs[ALBUM_NUM] = { m_purpleFoxTown, m_slipknot, m_vypsanaFixa, m_depeche, m_djo, m_ghost };


	bool m_songPlaying = false; // if song is playing

	// frame animating
	float frameCounter = 0;
	int currentFrame = 0;
	float frameIncrement = 0.05;

};

#endif // !GAME_HPP

