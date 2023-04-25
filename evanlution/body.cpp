#include "stdafx.h"
#include "body.h"

Body::Body(simData* simulationData, Body* parent_1, Body* parent_2)
{
	this->simulationData = simulationData;
	if (!parent_1 || !parent_2)
		this->genome = new Genome
		(
			this->simulationData->numGenes, this->simulationData->currentNumBodies
		);
	else
	{
		this->genome = new Genome(0, 0);
		this->genome->createChildGenome
		(
			parent_1->genome->genome, parent_2->genome->genome,
			this->simulationData->mutationRate
		);
	}
	this->neuralNetwork = new Net
	(
		std::vector<unsigned>{_max_input_,_max_hidden_,_max_output_}, 
		this->genome, this->simulationData
	);
	this->prevLocation = sf::Vector2i(-1, -1);

	this->body.setRadius(this->simulationData->tileSize / 2.f);
	this->body.setFillColor(sf::Color::Black);

	this->simulationData->currentNumBodies++;
	
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

void Body::setMovable(unsigned F, unsigned B, unsigned R, unsigned L) // 0 = no change, 1 = false, 2 = true
{
	if(F != 0)
		this->personalData.movableForward = (F == 2);
	if(B != 0)
		this->personalData.movableBackward = (B== 2);
	if(R != 0)
		this->personalData.movableRight = (R == 2);
	if(L != 0)
		this->personalData.movableLeft = (L == 2);
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
	this->forwardProp();
	this->neuralNetwork->feedForward();
}

void Body::handleNeuralOutputs()
{
	std::vector<double> neuralOuts = this->neuralNetwork->getOutputs();
	std::pair<outputNeurons, double> prev; prev.first = _max_output_; prev.second = 0.00;
	for (size_t i = 0; i < neuralOuts.size(); i++)
	{
		if (neuralOuts[i] > prev.second)
		{
			prev.second = neuralOuts[i];
			prev.first = static_cast<outputNeurons>(i);
		}
	}

	switch (prev.first)
	{
		//case Stl:
		//	//std::cout << "Stl"<<"\n";
		//	this->standStill();
		//	break;
	case MU:
		//std::cout << "MU" << "\n";
		this->moveUp();
		break;
	case MD:
		//std::cout << "MD" << "\n";
		this->moveDown();
		break;
	case MR:
		//std::cout << "MR" << "\n";
		this->moveRight();
		break;
	case ML:
		//std::cout << "ML" << "\n";
		this->moveLeft();
		break;
	case MRn:
		//std::cout << "MRn" << "\n";
		this->moveRandom();
		break;
	default:
		//std::cout << "Unk" << "\n";

		break;
	}

}

void Body::handleNeuralOutputsRand()
{
	std::vector<double> neuralOuts = this->neuralNetwork->getOutputs();
	double sumOfOuts = 0.0;
	srand((unsigned)time(NULL) / this->simulationData->seedVariable);
	double choice = (double) rand() / 32767;
	int chosenNeuron = 0;
	while (chosenNeuron < neuralOuts.size())
	{
		sumOfOuts += neuralOuts[chosenNeuron];
		//std::cout << choice<<"  "<<sumOfOuts << "\n";

		if (choice <= sumOfOuts)
		{
			//std::cout << "BREAK\n";
			break;
		}
		chosenNeuron++;
	}
	this->simulationData->seedVariable++;
	switch (chosenNeuron)
	{
	//case Stl:
	//	//std::cout << "Stl"<<"\n";
	//	this->standStill();
	//	break;
	case MU:
		//std::cout << "MU" << "\n";
		this->moveUp();
		break;
	case MD:
		//std::cout << "MD" << "\n";
		this->moveDown();
		break;
	case MR:
		//std::cout << "MR" << "\n";
		this->moveRight();
		break;
	case ML:
		//std::cout << "ML" << "\n";
		this->moveLeft();
		break;
	case MRn:
		//std::cout << "MRn" << "\n";
		this->moveRandom();
		break;
	default:
		//std::cout << "Unk" << "\n";

		break;
	}
}

void Body::update()
{
	this->step();
	this->handleNeuralOutputs();
	//this->handleNeuralOutputsRand();
}

void Body::render(sf::RenderWindow* window)
{
	window->draw(this->body);
}

void Body::standStill()
{
	//Stands still (does nothing)
}

void Body::moveUp()
{
	this->prevLocation = sf::Vector2i((int)this->getLocation().x, (int)this->getLocation().y);
	//std::cout << this->prevLocation.x << " " << this->prevLocation.y << "\n";
	if(this->getLocation().y > 0)
	this->setLocation(this->getLocation().x, this->getLocation().y - 1);
}

void Body::moveDown()
{
	this->prevLocation = sf::Vector2i((int)this->getLocation().x, (int)this->getLocation().y);
	//std::cout << this->prevLocation.x << " " << this->prevLocation.y << "\n";
	if (this->getLocation().y < this->simulationData->worldSize - 1)
	this->setLocation(this->getLocation().x, this->getLocation().y + 1);
}

void Body::moveRight()
{
	this->prevLocation = sf::Vector2i((int)this->getLocation().x, (int)this->getLocation().y);
	//std::cout << this->prevLocation.x << " " << this->prevLocation.y << "\n";
	if (this->getLocation().x < this->simulationData->worldSize - 1)
	this->setLocation(this->getLocation().x + 1, this->getLocation().y);
}

void Body::moveLeft()
{
	this->prevLocation = sf::Vector2i((int)this->getLocation().x, (int)this->getLocation().y);
	//std::cout << this->prevLocation.x << " " << this->prevLocation.y << "\n";
	if (this->getLocation().x > 0)
	this->setLocation(this->getLocation().x - 1, this->getLocation().y);
}

void Body::moveRandom()
{
	int dir = rand() % 4;
	switch (dir)
	{
	case 0:
		this->moveUp();
		break;
	case 1:
		this->moveDown();
		break;
	case 2:
		this->moveRight();
		break;
	case 3:
		this->moveLeft();
		break;
	default:
		break;
	}
}

void Body::forwardProp()
{	
	srand((unsigned)time(NULL) / this->simulationData->seedVariable);

	//AGE INPUT
	this->neuralNetwork->getNet()[INPUT][Age]->setInputNeuron
	(
		this->simulationData->globalStep / this->simulationData->maxSteps
	);

	//RND INPUT
	//this->neuralNetwork->getNet()[INPUT][Rnd]->setInputNeuron
	//(
	//	rand() % 32767
	//);

	//BFB INPUT
	if (!this->personalData.movableForward)
	{
		this->neuralNetwork->getNet()[INPUT][BFB]->setInputNeuron
		(
			1.0
		);
	}
	if (!this->personalData.movableBackward)
	{
		this->neuralNetwork->getNet()[INPUT][BFB]->setInputNeuron
		(
			-1.0
		);
	}

	//BRL INPUT
	if (!this->personalData.movableRight)
	{
		this->neuralNetwork->getNet()[INPUT][BRL]->setInputNeuron
		(
			1.0
		);
	}
	if (!this->personalData.movableLeft)
	{
		this->neuralNetwork->getNet()[INPUT][BRL]->setInputNeuron
		(
			-1.0
		);
	}

	//POP INPUT

	//BDx INPUT
	if (this->simulationData->worldSize - this->personalData.mapPosition.x 
		<
		this->personalData.mapPosition.x
		)
	{
		this->neuralNetwork->getNet()[INPUT][BDx]->setInputNeuron
		(
			(
				this->personalData.mapPosition.x - this->simulationData->worldSize / 2.0
			) 
			/ 
			(
				this->simulationData->worldSize / 2.0
			)
		);
	}
	else
	{
		this->neuralNetwork->getNet()[INPUT][BDx]->setInputNeuron
		(
			-(
				(
					this->simulationData->worldSize / 2.0
				) - this->personalData.mapPosition.x
			) 
			/ 
			(
				this->simulationData->worldSize / 2.0
			)
		);
	}

	//BDy INPUT
	if (this->simulationData->worldSize - this->personalData.mapPosition.y
		<
		this->personalData.mapPosition.y
		)
	{
		this->neuralNetwork->getNet()[INPUT][BDy]->setInputNeuron
		(
			-(
				this->personalData.mapPosition.y - this->simulationData->worldSize / 2.0
			) 
			/ 
			(
				this->simulationData->worldSize / 2.0
			)
		);
	}
	else
	{
		this->neuralNetwork->getNet()[INPUT][BDy]->setInputNeuron
		(
			(
				(
					this->simulationData->worldSize / 2.0
				) - this->personalData.mapPosition.y
			)
			/ 
			(
				this->simulationData->worldSize / 2.0
			)
		);
	}

	//BD INPUT

	//Lx
	this->neuralNetwork->getNet()[INPUT][Lx]->setInputNeuron
	(
		this->personalData.mapPosition.x - this->simulationData->worldSize
	);

	//Ly
	this->neuralNetwork->getNet()[INPUT][Ly]->setInputNeuron
	(
		this->personalData.mapPosition.y - this->simulationData->worldSize
	);
}

void Body::createGenome()
{
	//this->genome->createRandomGenome(this->simulationData->numGenes, 0, 0, this->simulationData->currentNumBodies);
}


