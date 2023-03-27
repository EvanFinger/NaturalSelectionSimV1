#ifndef NETWORK_VIEW_H
#define NETWORK_VIEW_H

#include "neuralNetwork.h"
#include "Line.h"

class networkView
{
public:
	networkView
	(
		simData* data, float pos_x, float pos_y, float width, float height, Net* neural_net = nullptr
	);
	~networkView();
	
	void render();
private:
	simData* simulationData;

	Net* neuralNet;

	sf::RectangleShape boundingRect;

	std::vector<sf::CircleShape> inputNeurons;
	std::vector<sf::CircleShape> hiddenNeurons;
	std::vector<sf::CircleShape> outputNeurons;

	std::vector<std::vector<sf::CircleShape>> visualNeuralNet =
	{
		std::vector<sf::CircleShape>(),
		std::vector<sf::CircleShape>(),
		std::vector<sf::CircleShape>()
	};

	std::vector<Line> synapses;

	void initNeuronVisuals();
	void drawSynapses();
};

#endif