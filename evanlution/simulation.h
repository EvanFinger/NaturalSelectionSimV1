#ifndef SIMULATION_H
#define SIMULATION_H

#include "simGui.h"
#include "simView.h"
#include "networkView.h"
#include "neuralNetwork.h"
#include "body.h"




class simulation
{
private:
	simData simulationData;

	simView* simulationView;
	networkView* netView;
	simGui* simulationGui;

	sf::RectangleShape bg;
	Line line;

	void initSimView();
	void initNetView();

public:
	simulation(unsigned window_width, unsigned window_height);
	~simulation();

	void restart();

	void update();
	void updateNetVisual();
	void updateSFEvents();

	void render();


	void run();
};

#endif