#ifndef LINE_H
#define LINE_H

class Line
{

private:

	sf::RectangleShape line;

public:
	Line();
	~Line();

	void setEndPoints(float x1, float y1, float x2, float y2);
	void setFillColor(sf::Color fillColor);
	void setThickness(float thickness);
	void setRotation(float angle);
	sf::FloatRect getGlobalBounds() const;

	void render(sf::RenderWindow* window);
};

#endif
