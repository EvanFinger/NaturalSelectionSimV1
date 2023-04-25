#include "stdafx.h"
#include "networkView.h"

networkView::networkView(simData* data, float pos_x, float pos_y, float width, float height, Net* neural_net)
{
	this->simulationData = data;
	this->neuralNet = neural_net;

	this->boundingRect.setPosition
	(
		sf::Vector2f(pos_x, pos_y)
	);
	this->boundingRect.setSize
	(
		sf::Vector2f(width, height)
	);
	this->boundingRect.setFillColor(sf::Color::Transparent);
	this->boundingRect.setOutlineThickness(1);
	this->boundingRect.setOutlineColor(sf::Color::White);

	this->initNeuronVisuals();
	this->drawSynapses();
}

networkView::~networkView()
{
}

void networkView::update()
{
	this->updateNeuronToggles();
}

void networkView::render()
{
	this->simulationData->window->draw(this->boundingRect);
	for (auto& it : this->synapses)
	{
		it.render(this->simulationData->window);
	}
	for (auto& it : this->visualNeuralNet[0])
	{
		this->simulationData->window->draw(it);
	}
	for (auto& it : this->visualNeuralNet[1])
	{
		this->simulationData->window->draw(it);
	}
	for (auto& it : this->visualNeuralNet[2])
	{
		this->simulationData->window->draw(it);
	}
}

void networkView::updateNeuronToggles()
{
	sf::Vector2f currentMousePosView = this->simulationData->window->mapPixelToCoords(sf::Mouse::getPosition(*this->simulationData->window));

	for (size_t layer = 0; layer < this->visualNeuralNet.size(); layer++)
	{
		for (size_t neuron = 0; neuron < this->visualNeuralNet[layer].size() - 1; neuron++)
		{
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (this->visualNeuralNet[layer][neuron].getGlobalBounds().contains(currentMousePosView))
				{
					if (!this->clicked)
					{
						this->simulationData->neuronToggleBools[layer][neuron] = !this->simulationData->neuronToggleBools[layer][neuron];
						this->clicked = true;
					}
				}
			}
			else
			{
				this->clicked = false;
			}
			this->updateNeuronShadings(this->simulationData->neuronToggleBools[layer][neuron], layer, neuron);
		}
	}
}

void networkView::updateNeuronShadings(bool active, int layer, int neuron)
{
	if (active)
	{
		this->visualNeuralNet[layer][neuron].setFillColor
		(
			sf::Color
			(
				this->visualNeuralNet[layer][neuron].getFillColor().r,
				this->visualNeuralNet[layer][neuron].getFillColor().g,
				this->visualNeuralNet[layer][neuron].getFillColor().b,
				255
			)
		);
	}
	else
	{
		this->visualNeuralNet[layer][neuron].setFillColor
		(
			sf::Color
			(
				this->visualNeuralNet[layer][neuron].getFillColor().r,
				this->visualNeuralNet[layer][neuron].getFillColor().g,
				this->visualNeuralNet[layer][neuron].getFillColor().b,
				155
			)
		);
	}
}

void networkView::initNeuronVisuals()
{
	float rad = 10.f;

	this->visualNeuralNet[0].resize(this->neuralNet->getNet()[0].size(), sf::CircleShape());
	for (int i = 0; i < this->visualNeuralNet[0].size(); i++)
	{
		this->visualNeuralNet[0][i].setRadius(rad);

		this->visualNeuralNet[0][i].setPosition
		(
			sf::Vector2f(
				this->boundingRect.getPosition().x + 
				(this->boundingRect.getGlobalBounds().width / 4) - this->visualNeuralNet[0][i].getGlobalBounds().width,
				this->boundingRect.getPosition().y + 
				(this->boundingRect.getGlobalBounds().height - 
					rad*2*this->visualNeuralNet[0].size()) / 2 + this->visualNeuralNet[0][i].getGlobalBounds().height * i
				)
		);

		this->visualNeuralNet[0][i].setFillColor(sf::Color::Magenta);
	}

	this->visualNeuralNet[1].resize(this->neuralNet->getNet()[1].size(), sf::CircleShape());
	for (int i = 0; i < this->visualNeuralNet[1].size(); i++)
	{
		this->visualNeuralNet[1][i].setRadius(rad);

		this->visualNeuralNet[1][i].setPosition
		(
			sf::Vector2f(
				this->boundingRect.getPosition().x + 
				(this->boundingRect.getGlobalBounds().width / 2) - this->visualNeuralNet[1][i].getGlobalBounds().width,
				this->boundingRect.getPosition().y + 
				(this->boundingRect.getGlobalBounds().height
					- rad * 2 * this->visualNeuralNet[1].size()) / 2 + this->visualNeuralNet[1][i].getGlobalBounds().height * i
			)
		);

		this->visualNeuralNet[1][i].setFillColor(sf::Color::Blue);
	}

	this->visualNeuralNet[2].resize(this->neuralNet->getNet()[2].size(), sf::CircleShape());
	for (int i = 0; i < this->visualNeuralNet[2].size(); i++)
	{
		this->visualNeuralNet[2][i].setRadius(rad);

		this->visualNeuralNet[2][i].setPosition
		(
			sf::Vector2f(
				this->boundingRect.getPosition().x + 
				(this->boundingRect.getGlobalBounds().width / 4)*3 - this->visualNeuralNet[2][i].getGlobalBounds().width,
				this->boundingRect.getPosition().y + 
				(this->boundingRect.getGlobalBounds().height - 
					rad * 2 * this->visualNeuralNet[2].size()) / 2 + this->visualNeuralNet[2][i].getGlobalBounds().height * i
			)
		);

		this->visualNeuralNet[2][i].setFillColor(sf::Color::Yellow);
	}
}

void networkView::drawSynapses()
{
	for (int layer = 0; layer < this->neuralNet->getNet().size(); layer++)
	{
		for (int neuron = 0; neuron < this->neuralNet->getNet()[layer].size(); neuron++)
		{
			for (int connection = 0; connection < this->neuralNet->getNet()[layer][neuron]->getConnections().size(); connection++)
			{
				int target_layer, target_neuron;
				target_layer = this->neuralNet->getNet()[layer][neuron]->getConnections()[connection]->target_Neuron->layer;
				target_neuron = this->neuralNet->getNet()[layer][neuron]->getConnections()[connection]->target_Neuron->neuron;

				this->synapses.push_back(Line());
				this->synapses.back().setEndPoints
				(
					this->visualNeuralNet[layer][neuron].getPosition().x + this->visualNeuralNet[layer][neuron].getGlobalBounds().width / 2,
					this->visualNeuralNet[layer][neuron].getPosition().y + this->visualNeuralNet[layer][neuron].getGlobalBounds().height / 2,
					this->visualNeuralNet[target_layer][target_neuron].getPosition().x + 
					this->visualNeuralNet[target_layer][target_neuron].getGlobalBounds().width / 2,
					this->visualNeuralNet[target_layer][target_neuron].getPosition().y + 
					this->visualNeuralNet[target_layer][target_neuron].getGlobalBounds().height / 2
				);
				if (this->neuralNet->getNet()[layer][neuron]->getConnections()[connection]->weight < 0)
					this->synapses.back().setFillColor(sf::Color::Red);
				else
					this->synapses.back().setFillColor(sf::Color::Green);

			}
		}
	}
}
