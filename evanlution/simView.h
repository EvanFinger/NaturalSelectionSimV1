#ifndef SIM_VIEW_H
#define SIM_VIEW_H



#include "simData.h"
#include "body.h"

struct Tile
{
	sf::RectangleShape tile;
	Body* inhabitant;
	bool spawnTile;
	bool locked;
};

class simView
{
private:
	simData* simulationData;

	sf::FloatRect viewBounds;

	sf::Vector2f position;
	sf::Vector2f resolution;
	sf::Vector2u numTiles;

	std::vector<std::vector<Tile>> tileMap;

	//Create zone variables
	int fromX = -1, fromY = -1, toX = -1, toY = -1;
	bool held = false;

	void updateBodyPositions();
	void updateSelectedBody();

	void createZones();
	void setSelectionBounds(sf::Vector2f mousePosition);
	void updateSelectedTiles();
	bool tilesSelected = false;
	

	void randomizePopulationLocation();

public:	
	std::vector<Body*> population;

	bool ready2render;
	unsigned generationID = 0;


	simView
	(
		simData* data,
		float pos_x, float pos_y,
		float width_pixels, float height_pixels, 
		unsigned width_tiles, unsigned height_tiles
	);
	~simView();

	void setPopulation(unsigned pop);

	void NextGeneration();

	void update();
	void render();

};

#endif