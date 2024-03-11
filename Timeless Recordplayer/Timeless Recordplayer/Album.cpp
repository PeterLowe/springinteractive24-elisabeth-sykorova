#include "Album.h"


Album::Album()
{

}


void Album::setup(float t_firstX, float t_firstY)
{
	int sideSize = 210; // x, size of album (x^2)
	sf::Vector2f firstPoint = { t_firstX, t_firstY }; // coordinates of top left point
	int angleBy = 50; // tilt in y axis

	int red = (rand() % 256) + 1;
	int green = (rand() % 256) + 1;
	int blue = (rand() % 256) + 1;
	int opacity = 255;
	

	m_cover[0].position = sf::Vector2f(firstPoint);
	/*m_cover[0].color = sf::Color(red, green, blue, opacity);*/

	m_cover[1].position = sf::Vector2f((firstPoint.x + sideSize), (firstPoint.y + angleBy));
	/*m_cover[1].color = sf::Color(red, green, blue, opacity);*/

	m_cover[2].position = sf::Vector2f((firstPoint.x + sideSize), (firstPoint.y + sideSize + angleBy));
	/*m_cover[2].color = sf::Color(red, green, blue, opacity);*/

	m_cover[3].position = sf::Vector2f(firstPoint.x, (firstPoint.y + sideSize));
	/*m_cover[3].color = sf::Color(red, green, blue, opacity);*/


	m_cover[0].texCoords = {0.0f, 0.0f};
	m_cover[1].texCoords = { 800.0f, 0.0f };
	m_cover[2].texCoords = { 800.0f,800.0f };
	m_cover[3].texCoords = { 0.0f,800.0f };


	
	// texture

	//if (!m_albumTexture.loadFromFile("ASSETS\\IMAGES\\purpleFoxTown.jpg"))
	//{
	//	// simple error message if previous call fails
	//	std::cout << "problem loading fox" << std::endl;
	//}

	//if (!m_fleetwoodTexture.loadFromFile("ASSETS\\IMAGES\\fleetwoodMac.jpg"))
	//{
	//	// simple error message if previous call fails
	//	std::cout << "problem loading fleet" << std::endl;
	//}


}

// moves all the points up by 1 pixel
void Album::moveUp()
{
	speed = { 0.0f, -0.25f };
	for (int index = 0; index < 4; index++)
	{
		m_cover[index].position += speed;
	}

}

void Album::moveDown()
{
	speed = { 0.0f, 0.25f };


}

bool Album::getRevealed()
{
	return m_revealed;
}

void Album::setRevealed(bool t_isRevealed)
{
	m_revealed = t_isRevealed;
}

void Album::setMoveUp(bool t_moveUp)
{
	m_moveUp = t_moveUp;
}

bool Album::getMoveUp()
{
	return m_moveUp;
}


