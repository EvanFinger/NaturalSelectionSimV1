#ifndef BODY_H
#define BODY_H

#include "neuralNetwork.h"

class Body
{
public:

	sf::Vector2i prevLocation;

	Body(simData* simulationData, Body* parent_1 = nullptr, Body* parent_2 = nullptr);
	~Body();

	void setLocation(unsigned x, unsigned y);
	void move(unsigned x, unsigned y);
	void setPosition(float x, float y);
	void setFillColor(sf::Color color);
	void setMovable(unsigned F, unsigned B, unsigned R, unsigned L);


	Net* getNeuralNet() const;
	sf::Vector2u getLocation() const;
	sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds() const;

	void step();
	
	void handleNeuralOutputs();
	void handleNeuralOutputsRand();
	void update();
	void render(sf::RenderWindow* window);
private:
	simData* simulationData;


	sf::CircleShape body;

	bodyData personalData;
	Net* neuralNetwork;
	Genome* genome;


	//ACTION FUNCTIONS
	void standStill();
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	void moveRandom();


    void forwardProp();
	void createGenome();
	void createNeuralNet();


	
};

#endif