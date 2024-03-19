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
		albums[index].setupCover(index); // first point of the first album relative to index

	}

	record.setup();
	setupRecordPlayer();
	setupMusic();
	setupBackground();
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
			processMouseReleased(newEvent);
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
	checkVinylAlbumCollision();

	if (albums[m_albumToReveal].m_revealAlbum && albums[m_albumToReveal].m_revealedBy < MAX_REVEALED_BY) // moves up record until revealed or switched
	{
		albums[m_albumToReveal].moveUp();
		albums[m_albumToReveal].m_revealedBy++;
	}
	else if (albums[m_albumToReveal].m_revealedBy >= MAX_REVEALED_BY) // when revealed
	{
		albums[m_albumToReveal].m_revealed = true;
	}

	for (int index = 0; index < ALBUM_NUM; index++) // if other albums have been fully or partially revealed but the revealing album has changed, hide
	{
		if (albums[index].m_revealedBy > 0 && index != m_albumToReveal)
		{
			albums[index].moveDown();
			albums[index].m_revealedBy--;
		}
		else if (albums[index].m_revealedBy > 0 && index != m_albumToReveal)
		{
			albums[m_albumToReveal].m_revealed = false;
		}
	}

	if (record.reveal && record.revealedBy < MAX_REVEALED_BY)
	{
		if (!record.setupForRevealing)
		{
			record.vinylPosition = sf::Vector2f(albums[m_albumToReveal].m_cover.getPosition().x - 127,
									albums[m_albumToReveal].m_cover.getPosition().y - 135);

			record.spriteColor.a = 255;
			record.m_vinylSprite.setColor(record.spriteColor);
			record.setupForRevealing = true;
		}
		record.moveRight();

		record.revealedBy++;
	}
	else if (record.revealedBy >= MAX_REVEALED_BY)
	{
		record.reveal = false;
		record.revealed = true;
	}

	if (record.hide && record.revealedBy > 0)
	{
		record.moveLeft();

		record.fadeOut(); // fades out when hiding

		record.revealedBy--;
	}
	else if (record.revealedBy <= 0)
	{
		record.setupForRevealing = false;
		record.revealed = false;
		record.hide = false;
	}

	if (m_vinylDropped)
	{
		animateRecordplayer();
	}
	else
	{
		m_recordPlayerSprite.setTexture(m_recordPlayerTexture);
	}
}

	

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_backgroundSprite);


	m_window.draw(m_recordPlayerSprite);
	//m_window.draw(m_recordPlayer); // recordplayer debug


	for (int index = ALBUM_NUM - 1; index >= 0; index--)
	{
		if ((record.revealed || record.reveal) && record.setupForRevealing && index == m_albumToReveal && !m_vinylDropped)
		{
		/*	m_window.draw(record.vinyl);*/ // draws vinyl if it's activated  debug
			m_window.draw(record.m_vinylSprite);
		}
		//m_window.draw(albums[index].m_cover); // covers debug
		m_window.draw(albums[index].m_coverSprite);
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
	if (record.revealed && !m_mouseReleased && m_mouseOnVinyl &&
		!(m_mouseDot.getGlobalBounds().intersects(albums[m_albumToReveal].m_cover.getGlobalBounds())))
	{
		m_mouseEnd = sf::Mouse::getPosition(m_window);
		m_mouseEndVector.x = static_cast<float>(m_mouseEnd.x);
		m_mouseEndVector.y = static_cast<float>(m_mouseEnd.y);
		record.followMouse(m_mouseEndVector);
		m_holdingVinyl = true;
	}
	// if true, calls function for vinyl that follows the mouse
}

void Game::setupRecordPlayer()
{
	const sf::Vector2f size {10.0f, 40.0f};
	m_recordPlayer.setFillColor(sf::Color::Green);
	m_recordPlayer.setSize(size);
	m_recordPlayer.setPosition(560.0f, 360.0f);

	// sprite
	if (!m_recordPlayerTexture.loadFromFile("ASSETS\\IMAGES\\recordPlayer.png"))
	{
		std::cout << "problem loading recpla" << std::endl;
	}

	if (!m_recordplayerActive1.loadFromFile("ASSETS\\IMAGES\\recordplayerActive.png"))
	{
		std::cout << "problem loading rp active 1" << std::endl;
	}

	if (!m_recordplayerActive2.loadFromFile("ASSETS\\IMAGES\\recordplayerActive2.png"))
	{
		std::cout << "problem loading rp active 2" << std::endl;
	}

	if (!m_recordplayerActive3.loadFromFile("ASSETS\\IMAGES\\recordplayerActive3.png"))
	{
		std::cout << "problem loading rp active 3" << std::endl;
	}

	m_recordPlayerSprite.setOrigin(180.0f, 205.0f);
	m_recordPlayerSprite.setPosition(580.0, 300.f);
	m_recordPlayerSprite.setScale(0.92, 0.92);
	m_recordPlayerSprite.setTexture(m_recordPlayerTexture);
}

void Game::animateRecordplayer()
{
	if (currentFrame == 0)
	{
		m_recordPlayerSprite.setTexture(m_recordplayerActive1);
		std::cout << "active 1" << std::endl;
	}
	else if (currentFrame == 1)
	{
		m_recordPlayerSprite.setTexture(m_recordplayerActive3);
		std::cout << "active 3" << std::endl;
	}

	currentFrame = static_cast<int>(frameCounter);
	frameCounter += frameIncrement;

	if (frameCounter > 2)
	{
		frameCounter = 0;
	}
}

void Game::processMouseWheel(sf::Event t_event)
{
	if (!record.revealed) // no more revealing once a vinyl is out
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

		albums[m_albumToReveal].m_revealAlbum = true; // reveals the album that was revealed by mouse wheel

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

		// when clicked again, vinyl hides and user can scroll again

	if (record.revealed) // checks when getting vinyl (it has been revealed), if mouse is on it (later used for mouse following)
	{
		m_mouseOnVinyl = m_mouseDot.getGlobalBounds().intersects(record.vinyl.getGlobalBounds());

		//if (m_mouseDot.getGlobalBounds().intersects(record.vinyl.getGlobalBounds()))
		//{
		//	m_mouseOnVinyl = true;
		//}
		//else
		//{
		//	m_mouseOnVinyl = false;
		//}
	}

}

void Game::processMouseReleased(sf::Event t_event)
{

	if (m_mouseDot.getGlobalBounds().intersects(albums[m_albumToReveal].m_cover.getGlobalBounds()) &&
		record.revealed)
	{
			record.hide = true;

	}

	if (albums[m_albumToReveal].m_revealedBy == MAX_REVEALED_BY && //only if fully revealed
		m_mouseDot.getGlobalBounds().intersects(albums[m_albumToReveal].m_cover.getGlobalBounds()) && // if mouse is on the album
		record.revealed != true)
	{
		record.reveal = true;

	}


}

void Game::checkVinylPlayerCollision()
{
	// if vinyl is released on recordplayer, music plays
	if (m_recordPlayer.getGlobalBounds().intersects(record.vinyl.getGlobalBounds()) && m_mouseReleased && m_songPlaying != true && record.revealed
		&& record.hide != true)
	{
		if (!m_vinylDropped)
		{
			m_vinylDropped = true;
			std::cout << "vinyl dropped";
			record.vinyl.setPosition(m_recordPlayer.getPosition().x + (m_recordPlayer.getSize().x)/ 2 - 50.0f,
									m_recordPlayer.getPosition().y + (m_recordPlayer.getSize().y) / 2); // 50.0f is offset for the texture to make sense

			record.m_vinylSprite.setPosition(m_recordPlayer.getPosition().x + (m_recordPlayer.getSize().x) / 2 - 50.0f,
				m_recordPlayer.getPosition().y + (m_recordPlayer.getSize().y) / 2);
		}
		switch(m_albumToReveal)
		{
			case 0:
				m_purpleFoxTown.play(); // REPLACE with an array 
				std::cout << "purpl playing" << std::endl;
				m_songPlaying = true;
				frameIncrement = 0.052;
				break;

			case 1:
				m_slipknot.play();
				std::cout << "slipk" << std::endl;
				m_songPlaying = true;
				frameIncrement = 0.1;
				break;

			case 2:
				m_vypsanaFixa.play();
				std::cout << "fix" << std::endl;
				m_songPlaying = true;
				break;

			case 3:
				m_depeche.play();
				std::cout << "depeche" << std::endl;
				m_songPlaying = true;
				break;

			case 4:
				m_djo.play();
				std::cout << "end of b" << std::endl;
				m_songPlaying = true;
				break;

			case 5:
				m_ghost.play();
				std::cout << "ghost playing" << std::endl;
				m_songPlaying = true;
				break;

		}

	}
	if ((m_songPlaying == true && !m_mouseReleased && m_mouseDot.getGlobalBounds().intersects(record.vinyl.getGlobalBounds())) ||
		record.hide)
	{
		if (m_vinylDropped)
		{
			m_vinylDropped = false;
			std::cout << "vinyl picked up ";
		}
		m_purpleFoxTown.stop();
		m_ghost.stop();
		m_slipknot.stop();
		m_djo.stop();
		m_vypsanaFixa.stop();
		m_depeche.stop();

		m_songPlaying = false;
	}
}

void Game::checkVinylAlbumCollision()
{
	if (albums[m_albumToReveal].m_cover.getGlobalBounds().intersects(record.vinyl.getGlobalBounds()) && m_mouseReleased && !record.reveal && m_holdingVinyl)
	{
		record.hide = true;

		m_holdingVinyl = false;
		m_hidingByDropping = true;

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

	if (!m_ghostBuffer.loadFromFile("ASSETS\\SOUNDS\\KissTheGoGoat.wav"))
	{
		std::cout << "problem loading mutter audio" << std::endl;
	}

	m_ghost.setBuffer(m_ghostBuffer);
	m_ghost.setVolume(20.0f);

	if (!m_slipknotBuffer.loadFromFile("ASSETS\\SOUNDS\\Custer.wav"))
	{
		std::cout << "problem loading slipknot audio" << std::endl;
	}

	m_slipknot.setBuffer(m_slipknotBuffer);
	m_slipknot.setVolume(20.0f);

	if (!m_depecheBuffer.loadFromFile("ASSETS\\SOUNDS\\EnjoyTheSilence.wav"))
	{
		std::cout << "problem loading enjoy the silence audio" << std::endl;
	}

	m_depeche.setBuffer(m_depecheBuffer);
	m_depeche.setVolume(20.0f);

	if (!m_djoBuffer.loadFromFile("ASSETS\\SOUNDS\\endOfBeginning.wav"))
	{
		std::cout << "problem loading djo audio" << std::endl;
	}

	m_djo.setBuffer(m_djoBuffer);
	m_djo.setVolume(20.0f);

	if (!m_vypsanaFixaBuffer.loadFromFile("ASSETS\\SOUNDS\\IvanTrojan.wav"))
	{
		std::cout << "problem loading fixa audio" << std::endl;
	}

	m_vypsanaFixa.setBuffer(m_vypsanaFixaBuffer);
	m_vypsanaFixa.setVolume(20.0f);


}

void Game::setupBackground()
{
	if (!m_backgroundTexture.loadFromFile("ASSETS\\IMAGES\\background.png"))
	{
		std::cout << "problem loading backgr" << std::endl;
	}

	m_backgroundSprite.setTexture(m_backgroundTexture);

}






