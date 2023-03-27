#include "stdafx.h"
#include "simulation.h"


void simulation::initSimView()
{
	this->simulationView = new simView
	(
		&this->simulationData,
		92.f, 92.f,
		896.f, 896.f, 
		this->simulationData.worldSize, this->simulationData.worldSize
	);
	this->simulationView->setPopulation(this->simulationData.populationBuffer);
	
	this->simulationGui = new simGui(&this->simulationData);
}

void simulation::initNetView()
{
	if(this->simulationView->population.size() > 0)
	this->netView = new networkView(&this->simulationData, 1004.f, 692.f, 900.f, 296.f, this->simulationView->population[0]->getNeuralNet());
}

simulation::simulation(unsigned window_width, unsigned window_height)
{

	this->simulationData.resolution.width = window_width;
	this->simulationData.resolution.height = window_height;
	this->simulationData.worldSize = 64;
	this->simulationData.worldSizeBuffer = 64;
	this->simulationData.numGenes = 100;
	this->simulationData.selectedBody = 0;

	this->simulationData.window = new sf::RenderWindow
	(
		simulationData.resolution, "Evanlution"
	);

	this->bg.setPosition(sf::Vector2f(0, 0));
	this->bg.setSize(sf::Vector2f(this->simulationData.resolution.width, this->simulationData.resolution.height));
	this->bg.setFillColor(sf::Color(110, 92, 181, 100));
	this->initSimView();
	this->initNetView();
}

simulation::~simulation()
{
	delete this->simulationView;
	delete this->netView;
	delete this->simulationGui;
}

void simulation::restart()
{
	delete this->simulationView;
	delete this->simulationGui;
	delete this->netView;

	this->simulationData.passBuffers();

	this->initSimView();
	this->initNetView();
}

void simulation::update()
{
	this->updateSFEvents();
	this->simulationView->update();
	this->simulationGui->masterUpdate();
	this->updateNetVisual();
	if (this->simulationGui->getRestart())
		this->restart();
}

void simulation::updateNetVisual()
{
	if (this->simulationData.selectedBody != this->simulationData.selectedBodyBuffer)
	{
		this->simulationView->population[this->simulationData.selectedBody]->setFillColor(sf::Color::Black);
		this->simulationData.selectedBody = this->simulationData.selectedBodyBuffer;
		delete this->netView;
		this->netView = new networkView(&this->simulationData, 1004.f, 692.f, 900.f, 296.f, this->simulationView->population[this->simulationData.selectedBody]->getNeuralNet());
		this->simulationView->population[this->simulationData.selectedBody]->setFillColor(sf::Color::Cyan);
	}
}

void simulation::updateSFEvents()
{
	sf::Event event;
	while (this->simulationData.window->pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
			this->simulationData.window->close();
	}
}

void simulation::render()
{
	this->simulationData.window->clear();
	this->simulationData.window->draw(this->bg);
	this->simulationView->render();

	if(this->netView)
	this->netView->render();


	this->simulationGui->masterRender();
	this->simulationData.window->display();
}

void simulation::run()
{
	while (this->simulationData.window->isOpen())
	{
		this->update();
		this->render();
	}
	
}
