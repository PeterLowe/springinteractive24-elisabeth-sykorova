/// <summary>
/// by Elisabeth Sykorova
/// March 2024
/// </summary>
/// 
/// NOTES: MAYBE GET RID OF SHAPES AND KEEP SPRITES ONLY?

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "Timeless Record Player by E.S." },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 

	for (int index = 0; index < ALBUM_NUM; index++) // setups all the covers based on the amount of albums declared
	{
		albums[index].setupCover(index); // first point of the first album relative to index
	}

	// all setups, happens once
	record.setup();
	setupRecordPlayer();
	setupMusic();
	setupBackground();
	setupBox();
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
		}
		if (sf::Event::MouseMoved == newEvent.type)
		{
			processMouseMovement(newEvent);
		}
		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			processMouseReleased(newEvent);
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

	if (sf::Keyboard::I == t_event.key.code) // toggle instructions
	{
		m_showInstructions = !m_showInstructions;
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

	if (albums[m_albumRevealed].m_revealAlbum && albums[m_albumRevealed].m_revealedBy < albums[m_albumRevealed].MAX_REVEAL_BY) // moves up record until revealed or switched
	{
		albums[m_albumRevealed].moveUp();
		albums[m_albumRevealed].m_revealedBy++;
	}
	else if (albums[m_albumRevealed].m_revealedBy == albums[m_albumRevealed].MAX_REVEAL_BY)
	{
		if (!m_holdingVinyl)
		{
			m_instructions.setString("CLICK  THE  CHOSEN  COVER  TO  TAKE  THE  VINYL  OUT");
		}
	}

	for (int index = 0; index < ALBUM_NUM; index++) // if other albums have been fully or partially revealed but the revealing album has changed, hide
	{
		if (albums[index].m_revealedBy > 0 && index != m_albumRevealed)
		{
			albums[index].moveDown();
			albums[index].m_revealedBy--;
		}
	}

	if (record.reveal && record.revealedBy < record.MAX_REVEAL_BY)
	{
		if (!record.setupForRevealing)
		{
			record.vinylPosition = sf::Vector2f(albums[m_albumRevealed].m_cover.getPosition().x - 127,
									albums[m_albumRevealed].m_cover.getPosition().y - 135);

			record.spriteColor.a = 255;
			record.m_vinylSprite.setColor(record.spriteColor);
			record.setupForRevealing = true;
		
		}
		record.moveRight();

		record.revealedBy++;
	}
	else if (record.revealedBy >= record.MAX_REVEAL_BY) // revealed
	{
		record.reveal = false;
		record.revealed = true;
		record.setupForHiding = false;

		if (!m_holdingVinyl)
		{
			m_instructions.setString("CLICK  AND  HOLD  THE  VINYL  TO  MOVE  IT");
		}
	}

	if (record.hide && record.revealedBy > 0)
	{
		if (!record.setupForHiding)
		{
			record.vinyl.setPosition(albums[m_albumRevealed].m_cover.getPosition().x + 20,
				albums[m_albumRevealed].m_cover.getPosition().y - 135);
			record.setupForHiding = true;
		}

		record.moveLeft();

		record.fadeOut(); // fades out when hiding

		record.revealedBy--;


		// NOTE: A FUNCTION THAT CHECKS THE POSITION OF THE VINYL WHEN IT'S BEING PUT AWAY COULD BE ADDED
		// AND BASED ON THAT THE DIRECTION/STYLE OF HIDING IT WOULD CHANGE
	}
	else if (record.revealedBy <= 0) // hidden
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

	if (m_showInstructions)
	{
		m_window.draw(m_instructions);
	}

	if (m_songPlaying)
	{
		m_window.draw(m_songTitle);
	}


	m_window.draw(m_recordPlayerSprite);
	//m_window.draw(m_recordPlayer); // recordplayer debug
	m_window.draw(m_boxBackSprite);

	for (int index = ALBUM_NUM - 1; index >= 0; index--)
	{
		if ((record.revealed || record.reveal) && record.setupForRevealing && index == m_albumRevealed && !m_vinylDropped)
		{
		/*	m_window.draw(record.vinyl);*/ // draws vinyl if it's activated  debug
			m_window.draw(record.m_vinylSprite);
		}
		//m_window.draw(albums[index].m_cover); // covers debug
		m_window.draw(albums[index].m_coverSprite);
	}

	m_window.draw(m_boxFrontSprite);


	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_font.loadFromFile("ASSETS\\FONTS\\VinylFont.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	// instructions
	m_instructions.setFont(m_font);
	m_instructions.setString("REVEAL  COVERS  USING  THE  SCROLL  WHEEL");
	m_instructions.setPosition(20.0f,565.0f);
	m_instructions.setFillColor(sf::Color::Black);
	m_instructions.setCharacterSize(16U);
	m_instructions.setStyle(sf::Text::Bold);

	// song playing
	m_songTitle.setFont(m_font);
	m_songTitle.setString("  Everblue  Forest\nby  Purplefox  Town");
	m_songTitle.setPosition(520.0f, 52.0f);
	m_songTitle.setFillColor(sf::Color::Black);
	m_songTitle.setCharacterSize(18U);
	m_songTitle.setStyle(sf::Text::Bold);

}


void Game::processMouseMovement(sf::Event t_event) // if mouse is moving 
{
	m_mouseEnd = sf::Mouse::getPosition(m_window);
	m_mouseEndVector.x = static_cast<float>(m_mouseEnd.x);
	m_mouseEndVector.y = static_cast<float>(m_mouseEnd.y);
	m_mouseDot.setPosition(m_mouseEndVector);

	// checks if vinyl is activated and revealed, if mouse is not revealed and if mouse is on colliding with vinyl
	// if true, calls function for vinyl that follows the mouse

	if (record.revealed && !m_mouseReleased && m_mouseOnVinyl &&
		!(m_mouseDot.getGlobalBounds().intersects(albums[m_albumRevealed].m_cover.getGlobalBounds())))
	{
		record.followMouse(m_mouseEndVector);

		if (!m_holdingVinyl)
		{
			m_holdingVinyl = true;
			m_instructions.setString("DRAG  THE  VINYL  ONTO  THE  RECORD  PLAYER  TO  PLAY  THE  TRACK");
		}
	}
}

void Game::setupRecordPlayer() // load textures, set position
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

void Game::animateRecordplayer() // when music is playing, recordplayer changes texture
{
	if (currentFrame == 0)
	{
		m_recordPlayerSprite.setTexture(m_recordplayerActive1);
		m_songTitle.setPosition(520.0f, 52.0f);
	}
	else if (currentFrame == 1)
	{
		m_recordPlayerSprite.setTexture(m_recordplayerActive3);
		m_songTitle.setPosition(520.0f, 58.0f);
	}

	currentFrame = static_cast<int>(frameCounter);
	frameCounter += frameIncrement;

	if (frameCounter > 2)
	{
		frameCounter = 0;
	}
}

void Game::processMouseWheel(sf::Event t_event) // scrolling through records
{
	if (!record.revealed && !record.reveal) // no more revealing once a vinyl is out or currently revealing
	{
		m_albumRevealed = m_albumRevealed + t_event.mouseWheel.delta; // mouse -1 or +1 based on direction of wheel movement

		if (m_albumRevealed < 0) // checks for array boundaries
		{
			m_albumRevealed = ALBUM_NUM - 1;
		}
		else if (m_albumRevealed >= ALBUM_NUM) // checks for array boundaries
		{
			m_albumRevealed = 0;
		}

		albums[m_albumRevealed].m_revealAlbum = true; // reveals the album that was revealed by mouse wheel

	}

}

void Game::processMousePressed(sf::Event t_event)
{
	m_mouseReleased = false;

	if (record.revealed) // checks when getting vinyl (it has been revealed), if mouse is on it (later used for mouse following)
	{
		m_mouseOnVinyl = m_mouseDot.getGlobalBounds().intersects(record.vinyl.getGlobalBounds()); // true or false
	}
}

void Game::processMouseReleased(sf::Event t_event)
{
	m_mouseReleased = true;

	if (m_mouseDot.getGlobalBounds().intersects(albums[m_albumRevealed].m_cover.getGlobalBounds()) &&
		record.revealed)
	{
			record.hide = true;
	}

	if (albums[m_albumRevealed].m_revealedBy == albums[m_albumRevealed].MAX_REVEAL_BY && //only if cover fully revealed
		m_mouseDot.getGlobalBounds().intersects(albums[m_albumRevealed].m_cover.getGlobalBounds()) && // if mouse is on the album
		record.revealed != true) // if vinyl is not already revealed
	{
		record.reveal = true; // starts revealing

	}


}

void Game::checkVinylPlayerCollision()
{
	// if vinyl is released on recordplayer, music plays
	if (m_recordPlayer.getGlobalBounds().intersects(record.vinyl.getGlobalBounds()) // vinyl on recordplayer(hitbox)
		&& m_mouseReleased // mouse released
		&& m_songPlaying != true // song is not already playing (otherwise it keeps resetting it)
		&& record.hide != true) // in case we start hiding it once its on the recordplayer (it would reset multiple times until it moves off the rp)
	{
		if (!m_vinylDropped) // makes the record disappear and reposition to a spot that makes sense for the rp texture vinyl (for picking up in the future)
		{
			m_vinylDropped = true;

			// circle shape
			record.vinyl.setPosition(m_recordPlayer.getPosition().x + (m_recordPlayer.getSize().x)/ 2 - 50.0f, // 50.0f is offset for the texture to make sense
									m_recordPlayer.getPosition().y + (m_recordPlayer.getSize().y) / 2);
			// sprite
			record.m_vinylSprite.setPosition(m_recordPlayer.getPosition().x + (m_recordPlayer.getSize().x) / 2 - 50.0f, // x
											m_recordPlayer.getPosition().y + (m_recordPlayer.getSize().y) / 2); // y

		}
		
		songs[m_albumRevealed].play();
		songs[m_albumRevealed].setLoop(true);


		// frame increment = (googled) BPM/60/60
		switch (m_albumRevealed)
		{
		case 0:
			m_songTitle.setString(" Everblue  Forest\nby  Purplefox  Town");
			frameIncrement = 0.052; 
			break;
		case 1:
			m_songTitle.setString("       Custer\n   by  Slipknot");
			frameIncrement = 0.091; 
			break;
		case 2:
			m_songTitle.setString("    Ivan Trojan\nby  Vypsana Fixa");
			frameIncrement = 0.066f; 
			break;
		case 3:
			m_songTitle.setString("Enjoy  the  Silence\n by  Depeche  Mode"); // formating using spaces 
			frameIncrement = 0.0627f; 
			break;
		case 4:
			m_songTitle.setString("End  of  Beginning\n        by  Djo");
			frameIncrement = 0.044f; 
			break;
		case 5:
			m_songTitle.setString("Kiss  The  Go  Goat\n     by  Ghost");
			frameIncrement = 0.072f; 
			break;
		}

		frameCounter = 0;

		m_instructions.setString("CLICK  AND  DRAG  THE  VINYL  BACK  TO  ITS  COVER  TO  PUT  IT  BACK");

		m_songPlaying = true;

	}
	if ((!m_mouseReleased && m_mouseDot.getGlobalBounds().intersects(record.vinyl.getGlobalBounds())) ||
		record.hide)
	{
		if (m_vinylDropped)
		{
			m_vinylDropped = false;
		}

		songs[m_albumRevealed].stop();

		m_songPlaying = false;
	}
}

void Game::checkVinylAlbumCollision()
{
	if (albums[m_albumRevealed].m_cover.getGlobalBounds().intersects(record.vinyl.getGlobalBounds())
		&& m_mouseReleased && m_holdingVinyl)
	{
		record.hide = true;
		m_holdingVinyl = false;
	}
}


void Game::setupMusic() // loads song
{
	if (!m_purpleFoxTownBuffer.loadFromFile("ASSETS\\SOUNDS\\EverblueForest.wav"))
	{
		std::cout << "problem loading fox audio" << std::endl;
	}

	songs[0].setBuffer(m_purpleFoxTownBuffer);
	songs[0].setVolume(20.0f);
	
	if (!m_ghostBuffer.loadFromFile("ASSETS\\SOUNDS\\KissTheGoGoat.wav"))
	{
		std::cout << "problem loading ghost audio" << std::endl;
	}

	songs[5].setBuffer(m_ghostBuffer);
	songs[5].setVolume(25.0f);


	if (!m_slipknotBuffer.loadFromFile("ASSETS\\SOUNDS\\Custer.wav"))
	{
		std::cout << "problem loading slipknot audio" << std::endl;
	}

	songs[1].setBuffer(m_slipknotBuffer);
	songs[1].setVolume(20.0f);


	if (!m_depecheBuffer.loadFromFile("ASSETS\\SOUNDS\\EnjoyTheSilence.wav"))
	{
		std::cout << "problem loading enjoy the silence audio" << std::endl;
	}

	songs[3].setBuffer(m_depecheBuffer);
	songs[3].setVolume(18.0f);

	if (!m_djoBuffer.loadFromFile("ASSETS\\SOUNDS\\endOfBeginning.wav"))
	{
		std::cout << "problem loading djo audio" << std::endl;
	}

	songs[4].setBuffer(m_djoBuffer);
	songs[4].setVolume(20.0f);


	if (!m_vypsanaFixaBuffer.loadFromFile("ASSETS\\SOUNDS\\IvanTrojan.wav"))
	{
		std::cout << "problem loading fixa audio" << std::endl;
	}

	songs[2].setBuffer(m_vypsanaFixaBuffer);
	songs[2].setVolume(20.0f);

}

void Game::setupBackground()
{
	if (!m_backgroundTexture.loadFromFile("ASSETS\\IMAGES\\background.png"))
	{
		std::cout << "problem loading backgr" << std::endl;
	}

	m_backgroundSprite.setTexture(m_backgroundTexture);

}

void Game::setupBox()
{
	sf::Vector2f position = sf::Vector2f(albums[ALBUM_NUM-1].m_cover.getPosition().x - 238.0f, albums[ALBUM_NUM - 1].m_cover.getPosition().y - 100.0f);

	//front
	if (!m_boxFrontTexture.loadFromFile("ASSETS\\IMAGES\\boxFront.png"))
	{
		std::cout << "problem loading front box" << std::endl;
	}

	m_boxFrontSprite.setTexture(m_boxFrontTexture);
	m_boxFrontSprite.setPosition(position);

	if (!m_boxFrontTexture.loadFromFile("ASSETS\\IMAGES\\boxFront.png"))
	{
		std::cout << "problem loading front box" << std::endl;
	}

	m_boxFrontSprite.setTexture(m_boxFrontTexture);
	m_boxFrontSprite.setPosition(position);

	if (!m_boxBackTexture.loadFromFile("ASSETS\\IMAGES\\boxBack.png"))
	{
		std::cout << "problem loading back box" << std::endl;
	}

	m_boxBackSprite.setTexture(m_boxBackTexture);
	m_boxBackSprite.setPosition(position);


}






