#ifndef SIM_DATA_H
#define SIM_DATA_H

#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"





struct simData
{
	sf::RenderWindow* window = nullptr;
	sf::VideoMode resolution = sf::VideoMode(0,0);

	unsigned worldSize = NULL;
	unsigned worldSizeBuffer = NULL;
	float tileSize = 0;
	


	unsigned globalStep = 0;
	unsigned maxSteps = 300;

	unsigned numGenes = 0;

	unsigned populationBuffer = 0;

	int selectedBody = NULL;
	int selectedBodyBuffer = NULL;
	unsigned currentNumBodies = 0;

	void passBuffers()
	{
		this->worldSize = worldSizeBuffer;
	}
};

struct bodyData
{
	sf::CircleShape* body = nullptr;

	sf::Vector2u mapPosition = sf::Vector2u(0, 0);
};


#endif
