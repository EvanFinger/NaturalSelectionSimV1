#include "stdafx.h"
#include "simView.h"

void simView::updateBodyPositions()
{
	for (auto& it : this->population)
	{
		if  (
			(it->getLocation().x >= 0 && it->getLocation().x < this->simulationData->worldSize) 
			&& 
			(it->getLocation().y >= 0 && it->getLocation().y < this->simulationData->worldSize)
			)
		{
			if (!this->tileMap[it->getLocation().x][it->getLocation().y].inhabitant)
			{
				if(it->prevLocation.x != -1)
				this->tileMap[it->prevLocation.x][it->prevLocation.y].inhabitant = nullptr;
				this->tileMap[it->getLocation().x][it->getLocation().y].inhabitant = it;
				
				

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
		///CHECK FOR LEFT MOVABLE
		if (it->getLocation().x == 0)
		{
			it->setMovable(0, 0, 0, 1);
		}
		else
		{
			if (this->tileMap
				[
					static_cast<
					std::vector<std::vector<Tile, std::allocator<Tile>>, 
					std::allocator<std::vector<Tile, std::allocator<Tile>>>>::size_type
					>(it->getLocation().x) - 1
				][it->getLocation().y].inhabitant)
			{
				it->setMovable(0, 0, 0, 1);
			}
			else
			{
				it->setMovable(0, 0, 0, 2);
			}
		}
		///CHECK FOR RIGHT MOVABLE
		if (it->getLocation().x == this->simulationData->worldSize - 1)
		{
			it->setMovable(0, 0, 1, 0);
		}
		else
		{
			if (this->tileMap
				[
					static_cast<
					std::vector<std::vector<Tile, std::allocator<Tile>>, 
				std::allocator<std::vector<Tile, std::allocator<Tile>>>>::size_type
				>(it->getLocation().x) + 1
				][it->getLocation().y].inhabitant)
			{
				it->setMovable(0, 0, 1, 0);
			}
			else
			{
				it->setMovable(0, 0, 2, 0);
			}
		}
		///CHECK FOR UP MOVABLE
		if (it->getLocation().y == 0)
		{
			it->setMovable(1, 0, 0, 0);
		}
		else
		{
			if (this->tileMap[it->getLocation().x]
				[
					static_cast<
					std::vector<Tile, std::allocator<Tile>>::size_type
					>(it->getLocation().y) - 1
				].inhabitant)
			{
				it->setMovable(1, 0, 0, 0);
			}
			else
			{
				it->setMovable(2, 0, 0, 0);
			}
		}
		///CHECK FOR DOWN MOVABLE
		if (it->getLocation().y == this->simulationData->worldSize - 1)
		{
			it->setMovable(0, 1, 0, 0);
		}
		else
		{
			if (this->tileMap[it->getLocation().x][
				static_cast<
					std::vector<Tile, std::allocator<Tile>>::size_type
				>(it->getLocation().y) + 1].inhabitant)
			{
				it->setMovable(0, 1, 0, 0);
			}
			else
			{
				it->setMovable(0, 2, 0, 0);
			}
		}
	}
}

void simView::updateSelectedBody()
{
	for (int body = 0; body < this->population.size(); body++)
	{
		if (
			this->population[body]->getGlobalBounds().contains
		(
			this->simulationData->window->mapPixelToCoords(sf::Mouse::getPosition(*this->simulationData->window))
		)
			)
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
				this->simulationData->selectedBodyBuffer = body;
	}
}

void simView::createZones()
{

	sf::Vector2f currentMousePosView = this->simulationData->window->mapPixelToCoords
	(
		sf::Mouse::getPosition(*this->simulationData->window)
	);

	//reset tile colors during tile selection
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) //Detect user input to trigger tile edit state
	{
		this->setSelectionBounds(currentMousePosView); //Sets bounds of selected tiles

		this->updateSelectedTiles(); //update the selected tiles within the bounds
	}

	if (!this->held) //reset variables
	{
		this->fromX = -1; this->fromY = -1; this->toX = -1; this->toY = -1;
		this->tilesSelected = false;
	}
}

void simView::setSelectionBounds(sf::Vector2f mousePosition)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //Detect user input to trigger tile filling
	{
		if (!this->held) //sets start coords of bounding box
		{
			this->fromX = static_cast<int>(mousePosition.x);
			this->fromY = static_cast<int>(mousePosition.y);
			this->toX = static_cast<int>(mousePosition.x);
			this->toY = static_cast<int>(mousePosition.y);
			this->held = true;
		}
		else //updates the end coord of bounding box
		{
			this->toX = static_cast<int>(mousePosition.x);
			this->toY = static_cast<int>(mousePosition.y);
		}
	}
	else //triggers when finished drawing box to lock in spawning
	{
		if (this->held)
			this->tilesSelected = true;
		this->held = false;
	}
}

void simView::updateSelectedTiles()
{
	//Create temporary floatrect to contain selected tiles
	sf::IntRect selection_bounds;
	selection_bounds.left = fromX;
	selection_bounds.top = fromY;
	selection_bounds.width = toX - fromX;
	selection_bounds.height = toY - fromY;

	//DEBUG std::cout << "FX : " << selection_bounds.left << "FY : " << selection_bounds.top << "TX : " << selection_bounds.width << "TY : " << selection_bounds.height << "\n";

	for (auto& it : this->tileMap)
	{
		for (auto& it2 : it)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) //Resets all tiles to default state
				it2.locked = false;
			if (!it2.locked)
			{
				it2.tile.setFillColor(sf::Color::White);
				it2.spawnTile = false;
			}
			if ((abs(selection_bounds.width) > 0 || abs(selection_bounds.height) > 0) ) //only run if tiles are selected
			{
				if (selection_bounds.contains(sf::Vector2i(it2.tile.getPosition())))
				{
					it2.tile.setFillColor(sf::Color::Blue);
					if (this->tilesSelected)//only run once spacebar is released
					{
						it2.spawnTile = true;
						it2.locked = true;
						it2.tile.setFillColor(sf::Color::Green);
					}
				}
			}		
		}
	}
}

void simView::randomizePopulationLocation()
{
	for (size_t b = 0; b < this->population.size(); b++)
	{
		for (auto &x : this->tileMap)
		{
			for (auto& y : x)
			{
				y.inhabitant = nullptr;
			}
		}
		while (true)
		{
			unsigned x = rand() % this->simulationData->worldSize;
			unsigned y = rand() % this->simulationData->worldSize;

			if (!this->tileMap[x][y].inhabitant)
			{
				this->population[b]->setLocation(x, y);
				
				break;
			}
		}
	}
	this->updateBodyPositions();
}

simView::simView
(
	simData* data, float pos_x, float pos_y, float width_pixels,
	float height_pixels, unsigned width_tiles, unsigned height_tiles
)
{
	this->simulationData = data;
	this->ready2render = true;

	this->viewBounds.left = pos_x;
	this->viewBounds.top = pos_y;
	this->viewBounds.width = width_pixels;
	this->viewBounds.height = height_pixels;

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
				sf::Vector2f
				(
					this->position.x + (this->simulationData->tileSize * i), 
					this->position.y + (this->simulationData->tileSize * j)
				)
			);
			this->tileMap[i][j].tile.setFillColor(sf::Color::White);
			this->tileMap[i][j].tile.setOutlineThickness(0);
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
	this->randomizePopulationLocation();
}

void simView::NextGeneration()
{
	this->ready2render = false;
	std::vector<Body*> prevGen;
	std::vector<Body*> nextGen;
	for (int i = 0; i < this->population.size(); i++)
	{
		if (
			(
		this->tileMap[this->population[i]->getLocation().x][this->population[i]->getLocation().y].spawnTile
			)
		   )
		{
			prevGen.push_back(this->population[i]);
		}
	}
	nextGen.resize(this->simulationData->population);

	size_t prevGenIndex = 0;
	for (size_t i = 0; i < nextGen.size(); i++)
	{
		if (prevGen.size() >= 2)
			nextGen[i] = new Body(this->simulationData, prevGen[prevGenIndex], prevGen[prevGenIndex + 0]);
		else
			nextGen[i] = new Body(this->simulationData);
		 
		if (prevGenIndex < prevGen.size() - 2)
		{
			prevGenIndex++;
		}
		else
		{
			prevGenIndex = 0;
		}
	}	

	for (auto& it : this->population)
	{
		delete it;
	}

	for (size_t i = 0; i < nextGen.size(); i++)
	{
		population[i] = nextGen[i];
	}
	this->randomizePopulationLocation();

	this->ready2render = true;
	this->generationID++;
	system("CLS");
	std::cout << this->generationID;
}

void simView::update()
{
	if (this->simulationData->createZone_mode)
	{
		this->createZones();
	}

	if (!this->simulationData->paused)
	{
		if (this->simulationData->globalStep < this->simulationData->maxSteps)
		{
			for (auto& it : this->population)
			{
				it->update();
			}
		}
		this->updateBodyPositions();
		this->simulationData->globalStep++;
	}
	this->updateSelectedBody();

	
	

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
