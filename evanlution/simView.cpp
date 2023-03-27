#include "stdafx.h"
#include "simView.h"

void simView::updateBodyPositions()
{
	for (auto it : this->population)
	{
		if ((it->getLocation().x >= 0 && it->getLocation().x <= this->simulationData->worldSize) && (it->getLocation().y >= 0 && it->getLocation().y < this->simulationData->worldSize))
		{
			if (!this->tileMap[it->getLocation().x][it->getLocation().y].inhabitant)
			{
				this->tileMap[it->getLocation().x][it->getLocation().y].inhabitant = it;
				this->tileMap[it->prevLocation.x][it->prevLocation.y].inhabitant = nullptr;

				this->tileMap[it->getLocation().x][it->getLocation().y].inhabitant->setPosition(
					this->tileMap[it->getLocation().x][it->getLocation().y].tile.getPosition().x,
					this->tileMap[it->getLocation().x][it->getLocation().y].tile.getPosition().y
				);
			}
		}
		else
		{
			it->setLocation(it->getLocation().x, it->getLocation().y-1);
		}
	}
}

void simView::updateSelectedBody()
{
	for (int body = 0; body < this->population.size(); body++)
	{
		if (this->population[body]->getGlobalBounds().contains(this->simulationData->window->mapPixelToCoords(sf::Mouse::getPosition(*this->simulationData->window))))
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
				this->simulationData->selectedBodyBuffer = body;
	}
}

simView::simView(simData* data, float pos_x, float pos_y, float width_pixels, float height_pixels, unsigned width_tiles, unsigned height_tiles)
{
	this->simulationData = data;

	this->resolution = sf::Vector2f(width_pixels, height_pixels);
	this->numTiles = sf::Vector2u(width_tiles, height_tiles);
	this->position = sf::Vector2f(pos_x, pos_y);
	this->simulationData->tileSize = this->resolution.x / this->numTiles.x;

	this->tileMap.resize(this->numTiles.x, std::vector<Tile>());
	for (size_t i = 0; i < numTiles.x; i++)
	{
		for (size_t j = 0; j < numTiles.y; j++)
		{
			this->tileMap[i].resize(this->numTiles.y, Tile());
			this->tileMap[i][j].tile.setSize
			(
				sf::Vector2f(this->resolution.x / this->numTiles.x, this->resolution.y / this->numTiles.y)
			);
			this->tileMap[i][j].tile.setPosition
			(
				sf::Vector2f(this->position.x + (this->simulationData->tileSize * i), this->position.y + (this->simulationData->tileSize * j))
			);
			this->tileMap[i][j].tile.setFillColor(sf::Color::White);
			this->tileMap[i][j].tile.setOutlineThickness(-1);
			this->tileMap[i][j].tile.setOutlineColor(sf::Color::Black);
			this->tileMap[i][j].inhabitant = nullptr;
		}
	}
}

simView::~simView()
{
	for (auto it : this->population)
	{
		delete it;
	}
}

void simView::setPopulation(unsigned pop)
{
	this->population.resize(pop);
	for (auto& it : this->population)
	{
		it = new Body(this->simulationData);
	}
	for (size_t b = 0; b < this->population.size(); b++)
	{
		
		while (true)
		{
			unsigned x = rand() % this->simulationData->worldSize, y = rand() % this->simulationData->worldSize;
			
			if (!this->tileMap[x][y].inhabitant)
			{
				this->population[b]->setLocation(x, y);
				
				break;
			}
		}
	}
	this->updateBodyPositions();
}

void simView::update()
{
	this->updateSelectedBody();

	if (this->simulationData->globalStep <= this->simulationData->maxSteps)
	{
		for (auto& it : this->population)
		{
			//it->step();
	
			//it->update();
			
		}
	}
	
	this->simulationData->globalStep++;
}

void simView::render()
{
	for (auto &it : this->tileMap)
	{
		for (auto &it2 : it)
		{
			this->simulationData->window->draw(it2.tile);
			if(it2.inhabitant)
				it2.inhabitant->render(this->simulationData->window);
		}
	}
}
