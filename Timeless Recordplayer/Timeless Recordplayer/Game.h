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

//const int NORTH = 1;
//const int SOUTH = 2;
//const int EAST = 3;
//const int WEST = 4;

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
	void animateRecordplayer();


	void processMouseWheel(sf::Event t_event);
	void processMousePressed(sf::Event t_event);
	void processMouseReleased(sf::Event t_event);

	void checkVinylPlayerCollision();
	void checkVinylAlbumCollision();

	void setupMusic();
	void setupBackground();

	//sf::Sound songs[ALBUM_NUM];
	//sf::Texture textures[ALBUM_NUM];


	//sf::RectangleShape square;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	//sf::Texture m_logoTexture; // texture used for sfml logo
	//sf::Sprite m_logoSprite; // sprite used for sfml logo
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
	bool m_vinylDropped = false;
	bool m_hidingByDropping = false;


	sf::RectangleShape m_recordPlayer;
	sf::Sprite m_recordPlayerSprite;
	sf::Texture m_recordPlayerTexture;
	sf::Texture m_recordplayerActive1;
	sf::Texture m_recordplayerActive2;
	sf::Texture m_recordplayerActive3;

	sf::Sprite m_backgroundSprite;
	sf::Texture m_backgroundTexture;


	//songs
	// Everblue Forest - Purple Fox Town
	sf::SoundBuffer m_purpleFoxTownBuffer;
	sf::Sound m_purpleFoxTown;

	// Mutter - Rammstein
	sf::SoundBuffer m_ghostBuffer;
	sf::Sound m_ghost;

	// Custer - Slipknot
	sf::SoundBuffer m_slipknotBuffer;
	sf::Sound m_slipknot;

	// Enjoy the Silence - Depeche Mode
	sf::SoundBuffer m_depecheBuffer;
	sf::Sound m_depeche;

	// End of the Beginning - DJO
	sf::SoundBuffer m_djoBuffer;
	sf::Sound m_djo;

	// Ivan Trojan - Vypsana fixa
	sf::SoundBuffer m_vypsanaFixaBuffer;
	sf::Sound m_vypsanaFixa;

	bool m_songPlaying = false;

	bool hidingSet = true;

	float frameCounter = 0;
	int currentFrame = 0;
	float frameIncrement = 0.052;

};

#endif // !GAME_HPP

