#ifndef SIM_DATA_H
#define SIM_DATA_H

#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"



	//NEURONS
	enum neuronLayers
	{
		INPUT = 0,
		HIDDEN,
		OUTPUT,
		NUM_LAYERS
	};

	enum inputNeurons
	{
		Age,
		//Rnd,     //Random
		BFB,     //Blocked Forward/backward (+/-)
		BRL,     //Blocked left/right (-/+)
		Pop,     //Population near
		BDx,     //Distance from Border (east/west)
		BDy,     //Distance from Border (north/south)
		BD,      //Closest Border
		Lx,      //Location X
		Ly,	 //Location Y
		_max_input_
	};

	enum hiddenNeurons
	{
		N0 = 0,
		N1,
		N2,
		N3,
		N4,
		_max_hidden_
	};

	enum outputNeurons
	{
		Stl = 0,
		MU,     //Move Forward
		MD,     //Move Backward
		MR,      //Move Right
		ML,      //Move Left
		MRn,     //Move Random Direction
		_max_output_
	};


struct simData
{
	sf::RenderWindow* window = nullptr;
	sf::VideoMode resolution = sf::VideoMode(0,0);
	sf::Clock dtClock;

	unsigned worldSize = NULL;
	unsigned worldSizeBuffer = NULL;
	float tileSize = 0;
	
	float dt;

	unsigned globalStep = 0;
	unsigned maxSteps = 200;
	bool running = false;

	unsigned numGenes = 0;
	unsigned seedVariable = 0;
	float mutationRate = 0.1;

	bool createZone_mode = true;
	bool paused = false;

	unsigned populationBuffer = 0;
	unsigned population = 0;

	int selectedBody = NULL;
	int selectedBodyBuffer = NULL;
	unsigned currentNumBodies = 0;

	//NEURON TOGGLES

	std::vector<std::vector<bool>> neuronToggleBools =
	{
		std::vector<bool>() = {true, true, true, true, true, true, true, true, true}, //input
		std::vector<bool>() = {true, true, true, true, true, true}, //hidden
		std::vector<bool>() = {true, true, true, true, true, true} //output
	};

	void passBuffers()
	{
		this->worldSize = worldSizeBuffer;
		this->currentNumBodies = 0;
		this->seedVariable = 1;
		this->globalStep = 0;
		this->population = populationBuffer;
	}
};

struct bodyData
{
	sf::CircleShape* body = nullptr;

	sf::Vector2u mapPosition = sf::Vector2u(0, 0);

	bool movableForward = true;
	bool movableBackward = true;
	bool movableRight = true;
	bool movableLeft = true;
};


#endif
