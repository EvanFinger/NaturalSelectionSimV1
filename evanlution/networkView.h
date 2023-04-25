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
	
	void update();
	void render();
private:
	simData* simulationData;

	Net* neuralNet;

	sf::RectangleShape boundingRect;

	std::vector<sf::CircleShape> inputRenderNeurons;
	std::vector<sf::CircleShape> hiddenRenderNeurons;
	std::vector<sf::CircleShape> outputRenderNeurons;

	std::vector<std::vector<sf::CircleShape>> visualNeuralNet =
	{
		std::vector<sf::CircleShape>(),
		std::vector<sf::CircleShape>(),
		std::vector<sf::CircleShape>()
	};

	std::vector<Line> synapses;

	void updateNeuronToggles();
	void updateNeuronShadings(bool active, int layer, int neuron);
	bool clicked = false;

	void initNeuronVisuals();
	void drawSynapses();
};

#endif