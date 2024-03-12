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

	for (int index = 0; index < ALBUM_NUM; index++) // setups all the covers based on the amount of albums declared
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
	checkVinylPlayerCollision(); // checks if vinyl is on record player - plays music if true
}

	

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);

	//if (!m_purpleFoxTexture.loadFromFile("ASSETS\\IMAGES\\purpleFoxTown.jpg"))
	//{
	//	// simple error message if previous call fails
	//	std::cout << "problem loading cover" << std::endl;
	//}

	//if (!m_fleetwoodTexture.loadFromFile("ASSETS\\IMAGES\\fleetwoodMac.jpg"))
	//{
	//	// simple error message if previous call fails
	//	std::cout << "problem loading fleet" << std::endl;
	//}

	m_window.draw(m_recordPlayer); // recordplayer

	for (int index = ALBUM_NUM - 1; index >= 0; index--)
	{
		m_window.draw(albums[index].m_cover); // covers
	}
	if (m_getVinyl)
	{
		m_window.draw(recordOne.vinyl); // draws vinyl if it's activated
	}

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


void Game::processMouseMovement(sf::Event t_event) // if mouse is moving 
{
	// checks if vinyl is activated and revealed, if mouse is not revealed and if mouse is on colliding with vinyl
	if (m_getVinyl && recordOne.revealed && !m_mouseReleased && m_mouseOnVinyl)
	{
		m_mouseEnd = sf::Mouse::getPosition(m_window);
		m_mouseEndVector.x = m_mouseEnd.x;
		m_mouseEndVector.y = m_mouseEnd.y;
		recordOne.followMouse(m_mouseEndVector);
		m_holdingVinyl = true;
	}
	// if true, calls function for vinyl that follows the mouse

}

void Game::setupRecordPlayer()
{
	const sf::Vector2f size {200.0f, 80.0f};
	m_recordPlayer.setFillColor(sf::Color::Green);
	m_recordPlayer.setSize(size);
	m_recordPlayer.setPosition(500.0f, 400.0f);
}




void Game::processMouseWheel(sf::Event t_event)
{
	if (!m_getVinyl) // no more revealing once a vinyl is out
	{
		m_albumRevealed = m_albumToReveal;
		m_albumToReveal = m_albumToReveal + t_event.mouseWheel.delta; // mouse -1 or +1 based on direction of wheel movement

		if (m_albumToReveal < 0) // checks for array boundaries
		{
			m_albumToReveal = ALBUM_NUM - 1;
		}
		else if (m_albumToReveal >= ALBUM_NUM) // checks for array boundaries
		{
			m_albumToReveal = 0;
		}


		albums[m_albumToReveal].reveal(); // reveals the album that was revealed by mouse wheel



		// optionally add option when all albums hide



		if (m_albumRevealed >= 0 && m_albumRevealed < ALBUM_NUM) // checks for boundaries
		{
			albums[m_albumRevealed].hide(); // hides the previously revealed album
		}
	}

}

void Game::processMousePressed(sf::Event t_event)
{
	// for getting vinyl out of album

	m_mouseEnd = sf::Mouse::getPosition(m_window); // relative to window
	m_mouseEndVector.x = m_mouseEnd.x;
	m_mouseEndVector.y = m_mouseEnd.y;
	m_mouseDot.setPosition(m_mouseEndVector);
	

	for (int index = 0; index < ALBUM_NUM; index++) // checks for all objects
	{
		// if the mouse clicks on revealed album, it will move vinyl 
		if (albums[index].revealed &&
			m_mouseDot.getGlobalBounds().intersects(albums[index].m_cover.getGlobalBounds()) &&
			m_getVinyl != true) 
		{
			m_getVinyl = true;
			recordOne.moveRight(albums[index].m_cover.getPosition());
			std::cout << "revealing vinyl for " << index << std::endl;
			break;

		}
		// when clicked again, vinyl hides and user can scroll again
		else if(albums[index].revealed &&
			m_mouseDot.getGlobalBounds().intersects(albums[index].m_cover.getGlobalBounds()) &&
			m_getVinyl == true) 
		{
			m_getVinyl = false;
			recordOne.moveRight(sf::Vector2f(0.0f,0.0f));
			std::cout << "hiding back" << std::endl;
			
		}
	}
	


	if (m_getVinyl) // checks when getting vinyl (it has been revealed), if mouse is on it (later used for mouse following)
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
	// if vinyl is released on recordplayer, music plays
	if (m_recordPlayer.getGlobalBounds().intersects(recordOne.vinyl.getGlobalBounds()) && m_mouseReleased && m_songPlaying != true)
	{
		switch(m_albumToReveal)
		{
			case 0:
				m_purpleFoxTown.play();
				std::cout << "music playing" << std::endl;
				m_songPlaying = true;
				break;

			case 1:
				m_rammstein.play();
				std::cout << "ram playing" << std::endl;
				m_songPlaying = true;
				break;
		}

	}
	if (m_songPlaying == true && !(m_recordPlayer.getGlobalBounds().intersects(recordOne.vinyl.getGlobalBounds())))
	{
		m_purpleFoxTown.stop();
		m_rammstein.stop();
		m_songPlaying = false;
	}
}

void Game::setupMusic() // loads song
{
	if (!m_purpleFoxTownBuffer.loadFromFile("ASSETS\\SOUNDS\\EverblueForest.wav"))
	{
		std::cout << "problem loading fox audio" << std::endl;
	}

	m_purpleFoxTown.setBuffer(m_purpleFoxTownBuffer);
	m_purpleFoxTown.setVolume(20.0f);

	if (!m_rammsteinBuffer.loadFromFile("ASSETS\\SOUNDS\\Mutter.wav"))
	{
		std::cout << "problem loading mutter audio" << std::endl;
	}

	m_rammstein.setBuffer(m_rammsteinBuffer);
	m_rammstein.setVolume(20.0f);

}





