#ifndef BODY_H
#define BODY_H

#include "neuralNetwork.h"

class Body
{
public:

	sf::Vector2u prevLocation;

	Body(simData* simulationData);
	~Body();

	void setLocation(unsigned x, unsigned y);
	void move(unsigned x, unsigned y);
	void setPosition(float x, float y);
	void setFillColor(sf::Color color);


	Net* getNeuralNet() const;
	sf::Vector2u getLocation() const;
	sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds() const;

	void step();
	

	void update();
	void render(sf::RenderWindow* window);
private:
	simData* simulationData;

	sf::CircleShape body;

	bodyData personalData;
	Net* neuralNetwork;
	Genome* genome;
    void neuralInput();
	void createGenome();
	void createNeuralNet();


	
};

#endif