#include "stdafx.h"
#include "body.h"

Body::Body(simData* simulationData)
{
	this->simulationData = simulationData;
	this->genome = new Genome();
	this->createGenome();
	this->neuralNetwork = new Net(std::vector<unsigned>{_max_input_,_max_hidden_,_max_output_}, this->genome);

	this->body.setRadius(this->simulationData->tileSize / 2.f);
	this->body.setFillColor(sf::Color::Black);

	this->simulationData->currentNumBodies++;

	for (size_t i = 0; i< this->neuralNetwork->getNet()[0].size() - 1; i++)
	{
		this->neuralNetwork->getNet()[0][i]->setInputNeuron(0.1);
	}
	this->neuralNetwork->feedForward();
	this->neuralNetwork->getOutputs();
	
}

Body::~Body()
{
	delete this->genome;
	delete this->neuralNetwork;
}

void Body::setLocation(unsigned x, unsigned y)
{
	this->personalData.mapPosition = sf::Vector2u(x, y);
}

void Body::move(unsigned x, unsigned y)
{
	this->personalData.mapPosition.x += x;
	this->personalData.mapPosition.y += y;
}

void Body::setPosition(float x, float y)
{
	this->body.setPosition(x, y);
}

void Body::setFillColor(sf::Color color)
{
	this->body.setFillColor(color);
}

Net* Body::getNeuralNet() const
{
	return this->neuralNetwork;
}

sf::Vector2u Body::getLocation() const
{
	return this->personalData.mapPosition;
}

sf::Vector2f Body::getPosition() const
{
	return this->body.getPosition();
}

sf::FloatRect Body::getGlobalBounds() const
{
	return this->body.getGlobalBounds();
}

void Body::step()
{
	//this->neuralInput();
}

void Body::update()
{
	
	system("CLS");
	this->prevLocation = this->personalData.mapPosition;
	this->step();
	
	switch (NULL)
	{
	case Stl:
		break;
	case MFd:
		if (this->personalData.mapPosition.y > 0)
			this->personalData.mapPosition.y--;
		break;
	case MRn:

		break;
	case MBw:

		break;
	case MRL:

		break;
	case MX:

		break;
	case MY:

		break;
	default:

		break;
	}
}

void Body::render(sf::RenderWindow* window)
{
	window->draw(this->body);
}

void Body::neuralInput()
{	
}

void Body::createGenome()
{
	this->genome->createRandomGenome(this->simulationData->numGenes, 0, 0, this->simulationData->currentNumBodies);
}


