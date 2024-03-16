/// <summary>
/// by Elisabeth Sykorova
/// March 2024
/// </summary>
/// 
/// NOTES: GET RID OF ACCESSIVE BOOLS, REPLACE MOVE RIGHT OF VINYL TO UPDATE 

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

	if (albums[m_albumToReveal].revealAlbum && albums[m_albumToReveal].revealedBy < 50) // moves up record until revealed or switched
	{
		albums[m_albumToReveal].moveUp();
		albums[m_albumToReveal].revealedBy++;
		std::cout << m_albumToReveal << "revealed by " << albums[m_albumToReveal].revealedBy << std::endl;
	}
	else if (albums[m_albumToReveal].revealedBy >= 50) // when revealed
	{
		albums[m_albumToReveal].revealed = true;
	}

	for (int index = 0; index < ALBUM_NUM; index++) // if other albums have been fully or partially revealed but the revealing album has changed, hide
	{
		if (albums[index].revealedBy > 0 && index != m_albumToReveal)
		{
			albums[index].moveDown();
			albums[index].revealedBy--;
			std::cout << index << "revealed by " << albums[index].revealedBy << std::endl;
		}
		else if (albums[index].revealedBy > 0 && index != m_albumToReveal)
		{
			albums[m_albumToReveal].revealed = false;
		}
	}
}

	

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);

	m_window.draw(m_recordPlayer); // recordplayer

	for (int index = ALBUM_NUM - 1; index >= 0; index--)
	{
		m_window.draw(albums[index].m_cover); // covers
	}
	if (recordOne.revealed)
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
	if (recordOne.revealed && !m_mouseReleased && m_mouseOnVinyl)
	{
		m_mouseEnd = sf::Mouse::getPosition(m_window);
		m_mouseEndVector.x = static_cast<float>(m_mouseEnd.x);
		m_mouseEndVector.y = static_cast<float>(m_mouseEnd.y);
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
	if (!recordOne.revealed) // no more revealing once a vinyl is out
	{
		m_albumToReveal = m_albumToReveal + t_event.mouseWheel.delta; // mouse -1 or +1 based on direction of wheel movement

		if (m_albumToReveal < 0) // checks for array boundaries
		{
			m_albumToReveal = ALBUM_NUM - 1;
		}
		else if (m_albumToReveal >= ALBUM_NUM) // checks for array boundaries
		{
			m_albumToReveal = 0;
		}

		albums[m_albumToReveal].revealAlbum = true; // reveals the album that was revealed by mouse wheel

	}

}

void Game::processMousePressed(sf::Event t_event)
{
	// for getting vinyl out of album

	m_mouseEnd = sf::Mouse::getPosition(m_window); // relative to window
	m_mouseEndVector.x = static_cast<float>(m_mouseEnd.x);
	m_mouseEndVector.y = static_cast<float>(m_mouseEnd.y);
	m_mouseDot.setPosition(m_mouseEndVector);
	

		// if the mouse clicks on revealed album, it will move vinyl 
	if (albums[m_albumToReveal].revealedBy == 50 && //only if fully revealed
		m_mouseDot.getGlobalBounds().intersects(albums[m_albumToReveal].m_cover.getGlobalBounds()) && // if mouse is on the album
		recordOne.revealed != true) 
	{
		recordOne.moveRight(albums[m_albumToReveal].m_cover.getPosition());
		std::cout << "revealing vinyl for " << m_albumToReveal << std::endl;
		recordOne.revealed = true;

	}
		// when clicked again, vinyl hides and user can scroll again
	else if(m_mouseDot.getGlobalBounds().intersects(albums[m_albumToReveal].m_cover.getGlobalBounds()) &&
			recordOne.revealed == true) 
	{
		recordOne.moveRight(sf::Vector2f(0.0f,0.0f));
		std::cout << "hiding back" << std::endl;
		recordOne.revealed = false; 
			
	}		

	if (recordOne.revealed) // checks when getting vinyl (it has been revealed), if mouse is on it (later used for mouse following)
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
				m_purpleFoxTown.play(); // REPLACE with an array 
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

void Game::loadTextures()
{
	if (!m_purpleFoxTexture.loadFromFile("ASSETS\\IMAGES\\purpleFoxTown.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading fox" << std::endl;
	}


	if (!m_fleetwoodTexture.loadFromFile("ASSETS\\IMAGES\\fleetwoodMac.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading fleet" << std::endl;
	}




}





