#include "stdafx.h"
#include "Line.h"

Line::Line()
{
}

Line::~Line()
{
}

void Line::setEndPoints(float x1, float y1, float x2, float y2)
{
	this->line.setPosition
	(
		sf::Vector2f(x1, y1)
	);

	this->line.setSize
	(
		sf::Vector2f(
			sqrtf(powf((x2 - x1), 2) + powf((y2 - y1), 2)),
			1.f
		)
	);

	this->line.setRotation(atanf((y2 - y1) / (x2 - x1)) * (180/3.14));
}

void Line::setFillColor(sf::Color fillColor)
{
	this->line.setFillColor(fillColor);
}

void Line::setThickness(float thickness)
{
	this->line.setSize
	(
		sf::Vector2f(
			this->line.getGlobalBounds().width,
			thickness
		)
	);
}

void Line::setRotation(float angle)
{
	this->line.setRotation(angle);
}

sf::FloatRect Line::getGlobalBounds() const
{
	return this->line.getGlobalBounds();
}

void Line::render(sf::RenderWindow* window)
{
	window->draw(this->line);
}
