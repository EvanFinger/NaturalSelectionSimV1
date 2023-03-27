#ifndef SIM_VIEW_H
#define SIM_VIEW_H



#include "simData.h"
#include "body.h"

struct Tile
{
	sf::RectangleShape tile;
	Body* inhabitant;
};

class simView
{
private:
	simData* simulationData;

	sf::Vector2f position;
	sf::Vector2f resolution;
	sf::Vector2u numTiles;

	std::vector<std::vector<Tile>> tileMap;

	void updateBodyPositions();
	void updateSelectedBody();

public:	
	std::vector<Body*> population;

	simView
	(
		simData* data,
		float pos_x, float pos_y,
		float width_pixels, float height_pixels, 
		unsigned width_tiles, unsigned height_tiles
	);
	~simView();

	void setPopulation(unsigned pop);

	void update();
	void render();

};

#endif