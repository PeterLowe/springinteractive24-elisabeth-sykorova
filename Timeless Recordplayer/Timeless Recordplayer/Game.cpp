/// <summary>
/// by Elisabeth Sykorova
/// March 2024
/// </summary>
/// 
/// NOTES: 

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	
	//albums[0].setupQuadAlbum();

	for (int index = 0; index < ALBUM_NUM; index++)
	{
		// setup albums
	}

	for (int index = 0; index < ALBUM_NUM; index++)
	{
		albums[index].setupCover(250.0f + (index * 20.0f), 450.0f - (index * 30.0f));
	}
	recordOne.setup();
	setupRecordPlayer();
	setupMusic();



}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseWheelMoved == newEvent.type)
		{
			processMouseWheel(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type)
		{
			processMousePressed(newEvent);
			m_mouseReleased = false;
		}

		if (sf::Event::MouseMoved == newEvent.type)
		{
			processMouseMovement(newEvent);
		}
		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			m_mouseReleased = true;
		}
		
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	checkVinylPlayerCollision();
}

	

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	//m_window.draw(m_welcomeMessage);
	//m_window.draw(m_logoSprite);
	/*m_window.draw(m_angledAlbum);*/

	//m_window.draw(albums[9].m_angledAlbum); // for debug 

	if (!m_purpleFoxTexture.loadFromFile("ASSETS\\IMAGES\\purpleFoxTown.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading cover" << std::endl;
	}

	if (!m_fleetwoodTexture.loadFromFile("ASSETS\\IMAGES\\fleetwoodMac.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading fleet" << std::endl;
	}

	for (int index = ALBUM_NUM - 1; index >= 0; index--)
	{
		m_window.draw(albums[index].m_cover);
	}
	if (m_getVinyl)
	{
		m_window.draw(recordOne.vinyl);
	}

	m_window.draw(m_recordPlayer);
	
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}


void Game::processMouseMovement(sf::Event t_event)
{
	if (m_getVinyl && recordOne.revealed == true && m_mouseReleased != true && m_mouseOnVinyl)
	{
		m_mouseEnd = sf::Mouse::getPosition(m_window);
		m_mouseEndVector.x = m_mouseEnd.x;
		m_mouseEndVector.y = m_mouseEnd.y;
		recordOne.followMouse(m_mouseEndVector);
		m_holdingVinyl = true;
	}

}

void Game::setupRecordPlayer()
{
	const sf::Vector2f size {200.0f, 40.0f};
	m_recordPlayer.setFillColor(sf::Color::Green);
	m_recordPlayer.setSize(size);
	m_recordPlayer.setPosition(500.0f, 400.0f);
}

void Game::hovering()
{

}


void Game::reveal(int t_index)
{
	// reveal album

}

void Game::hide(int t_index)
{
	// hide album
}

void Game::processMouseWheel(sf::Event t_event)
{
	m_albumRevealed = m_albumToReveal;
	m_albumToReveal = m_albumToReveal + t_event.mouseWheel.delta;


	if (m_albumToReveal < 0)
	{
		m_albumToReveal = ALBUM_NUM - 1;
	}
	else if (m_albumToReveal >= ALBUM_NUM)
	{
		m_albumToReveal = 0;
	}
	albums[m_albumToReveal].reveal(); 
	
	// optionally add option when all albums hide
	
	

	if (m_albumRevealed >= 0 && m_albumRevealed < ALBUM_NUM)
	{
		albums[m_albumRevealed].hide();
	}

}

void Game::processMousePressed(sf::Event t_event)
{
	// for getting vinyl out of album

	m_mouseEnd = sf::Mouse::getPosition(m_window);
	m_mouseEndVector.x = m_mouseEnd.x;
	m_mouseEndVector.y = m_mouseEnd.y;
	m_mouseDot.setPosition(m_mouseEndVector);
	

	for (int index = 0; index < ALBUM_NUM; index++)
	{
		if (albums[index].revealed)
		{
			if (m_mouseDot.getGlobalBounds().intersects(albums[index].m_cover.getGlobalBounds()))
			{
				m_getVinyl = true;
				recordOne.moveRight(albums[index].m_cover.getPosition());
				std::cout << "revealing vinyl for " << index << std::endl;
			}
		}
	}

	if (m_getVinyl)
	{
		if (m_mouseDot.getGlobalBounds().intersects(recordOne.vinyl.getGlobalBounds()))
		{
			m_mouseOnVinyl = true;
		}
		else
		{
			m_mouseOnVinyl = false;
		}
	}

}

void Game::checkVinylPlayerCollision()
{


	if (m_recordPlayer.getGlobalBounds().intersects(recordOne.vinyl.getGlobalBounds()) && m_mouseReleased && m_songPlaying != true)
	{
		m_song.play();
		std::cout << "music playing" << std::endl;
		m_songPlaying = true;
	}
}

void Game::setupMusic()
{
	if (!m_songBuffer.loadFromFile("ASSETS\\SOUNDS\\EverblueForest.wav"))
	{
		std::cout << "problem loading background audio" << std::endl;
	}

	m_song.setBuffer(m_songBuffer);
}





