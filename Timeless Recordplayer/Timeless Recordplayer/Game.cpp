/// <summary>
/// by Elisabeth Sykorova
/// March 2024
/// </summary>
/// 
/// NOTES: - variables declared all over the place, in need of re-ordering
/// - BUG when hovering over first and unhovering in the direction down
/// REPLACE FOR LOOPS WITH IF
/// QUADS????

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
	setupSprite(); // load textur
	recordOne.setup();
	//albums[0].setupQuadAlbum();

	for (int index = 0; index < ALBUM_NUM; index++)
	{
		albums[index].setup(50.0f + (index * albumScatterX), 250.0f - (index * albumScatterY));
		std::cout << "setup " << index << std::endl;
	}



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
		if (sf::Event::MouseMoved == newEvent.type)
		{
			processMouseMovement(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type)
		{
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

	hovering();

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
		if (index % 2 == 0)
		{
			m_window.draw(albums[index].m_cover, &m_fleetwoodTexture);
		}
		else
		{
			m_window.draw(albums[index].m_cover, &m_purpleFoxTexture);
		}
	}

	m_window.draw(recordOne.vinyl);


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

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(300.0f, 180.0f);
}

void Game::processMouseMovement(sf::Event t_event)
{
	m_mouseEnd.x = static_cast<float>(t_event.mouseMove.x);
	m_mouseEnd.y = static_cast<float>(t_event.mouseMove.y);

	m_mouseDot.setPosition(m_mouseEnd); // tracking location of mouse to check if it intersects with a vertex

	for (int index = 0; index < ALBUM_NUM; index++)
	{
		if (m_mouseDot.getGlobalBounds().intersects(albums[index].m_cover.getBounds()))
		{
			albums[index].m_intersecting = true;
		}
		else
		{
			albums[index].m_intersecting = false;
		}
	}

}

void Game::hovering()
{
	int revealedIndex = ALBUM_NUM;
	int newIndex = ALBUM_NUM;
	bool foundIntersect = false;

	for (int index = 0; index < ALBUM_NUM; index++)
	{
		if (albums[index].m_intersecting)
		{
			if (foundIntersect == false)
			{
				revealedIndex = index;
				newIndex = index;
				reveal(index);
				foundIntersect = true;
			}
			else
			{
				revealedIndex = newIndex;
				newIndex = index;
				if (newIndex <= revealedIndex)
				{
					reveal(index);
					hide(revealedIndex);
				}
			}
		}
		else
		{
			hide(index);

		}
	}
}

void Game::reveal(int t_index)
{
	std::cout << "revealing index " << t_index << std::endl;
	if (albums[t_index].m_moveUpBy < 15)
	{
		albums[t_index].moveUp();
		albums[t_index].m_moveUpBy++;
	}
}

void Game::hide(int t_index)
{
	if (albums[t_index].m_moveUpBy > 0)
	{
		albums[t_index].moveDown();
		albums[t_index].m_moveUpBy--;
	}
}





