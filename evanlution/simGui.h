#ifndef SIM_GUI_H
#define SIM_GUI_H

#include"simData.h"
#include "sfml_gui.h"

struct PopulationSelector
{
public:
	PopulationSelector
	(
		sf::RenderWindow* window, float x_pos, float y_pos,
		float button_width, float selection_display_width, float height,
		sf::Font& font, unsigned short font_size,
		unsigned short max_population, unsigned short default_selection = 0
	)
		:font(font)
	{
		this->parentWindow = window;

		this->maxPopulation = max_population;

		this->selectedPopulation = default_selection;

		this->btns["dwn_thousand"] = new sfGUI::Button
		(
			this->parentWindow, x_pos, y_pos,
			button_width, height, this->font, 20, "-1000",
			0
		);
		this->btns["dwn_hundred"] = new sfGUI::Button
		(
			this->parentWindow, x_pos + button_width, y_pos,
			button_width, height, this->font, 20, "-100",
			1
		);
		this->btns["dwn_ten"] = new sfGUI::Button
		(
			this->parentWindow, x_pos + button_width * 2, y_pos,
			button_width, height, this->font, 20, "-10",
			2
		);
		this->btns["dwn_one"] = new sfGUI::Button
		(
			this->parentWindow, x_pos + button_width * 3, y_pos,
			button_width, height, this->font, 20, "-1",
			3
		);

		this->selectionDisplay.setPosition
		(
			sf::Vector2f(x_pos + button_width * 4, y_pos)
		);
		this->selectionDisplay.setSize
		(
			sf::Vector2f(selection_display_width, height)
		);

		this->selectionText.setFont(this->font);
		this->selectionText.setCharacterSize(font_size);
		this->selectionText.setFillColor(sf::Color::White);
		this->selectionText.setString(std::to_string(default_selection));
		this->selectionText.setPosition
		(
			sf::Vector2f(
				this->selectionDisplay.getPosition().x + this->selectionDisplay.getGlobalBounds().width / 2 - this->selectionText.getGlobalBounds().width / 2,
				this->selectionDisplay.getPosition().y + this->selectionDisplay.getGlobalBounds().height / 2 - this->selectionText.getGlobalBounds().height / 2
				)
		);

		this->btns["up_one"] = new sfGUI::Button
		(
			this->parentWindow, x_pos + button_width * 4 + this->selectionDisplay.getGlobalBounds().width, y_pos,
			button_width, height, this->font, 20, "+1",
			4
		);
		this->btns["up_ten"] = new sfGUI::Button
		(
			this->parentWindow, x_pos + button_width * 5 + this->selectionDisplay.getGlobalBounds().width, y_pos,
			button_width, height, this->font, 20, "+10",
			5
		);
		this->btns["up_hundred"] = new sfGUI::Button
		(
			this->parentWindow, x_pos + button_width * 6 + this->selectionDisplay.getGlobalBounds().width, y_pos,
			button_width, height, this->font, 20, "+100",
			6
		);
		this->btns["up_thousand"] = new sfGUI::Button
		(
			this->parentWindow, x_pos + button_width * 7 + this->selectionDisplay.getGlobalBounds().width, y_pos,
			button_width, height, this->font, 20, "+1000",
			7
		);
		
		
	}

	virtual ~PopulationSelector()
	{
		for (auto& btn : this->btns)
		{
			delete btn.second;
		}
	}

	void setArrowColors
	(
		sf::Color idle,
		sf::Color hover,
		sf::Color active
	)
	{
		this->btnIdle = idle;
		this->btnHover = hover;
		this->btnActive = active;

		for (auto& btn : this->btns)
		{
			btn.second->setBoundingRectColors(this->btnIdle, this->btnHover, this->btnActive);
		}
	}

	void setDisplayColors(sf::Color bg, sf::Color txt)
	{
		this->displayColor = bg;
		this->selectionDisplay.setFillColor(this->displayColor);
		this->txtColor = txt;
	}

	const int getPop() const
	{
		return this->selectedPopulation;
	}

	const sf::Vector2f getPosition() const
	{
		sf::Vector2f tmp = sf::Vector2f(
			this->btns.begin()->second->getBoundingRect()->getPosition().x,
			this->btns.begin()->second->getBoundingRect()->getPosition().y
		);
		return tmp;
	}
	
	const sf::FloatRect getGlobalBounds()
	{
		sf::FloatRect tmp = sf::FloatRect(
			this->btns["dwn_thousand"]->getBoundingRect()->getPosition().x,
			this->btns["dwn_thousand"]->getBoundingRect()->getPosition().y,
			this->btns["dwn_thousand"]->getBoundingRect()->getGlobalBounds().width*6 + this->selectionDisplay.getGlobalBounds().width,
			this->btns["dwn_thousand"]->getBoundingRect()->getGlobalBounds().height
		);
		return tmp;
	}

	void updateText()
	{
		this->selectionText.setString(std::to_string(this->selectedPopulation));
	}

	void update()
	{
		for (auto& btn : this->btns)
		{
			btn.second->update();
		}

		if (this->btns["dwn_thousand"]->getState() == BTN_RELEASED)
		{
			this->selectedPopulation -= 1000;
		}
		if (this->btns["dwn_hundred"]->getState() == BTN_RELEASED)
		{
			this->selectedPopulation -= 100;

		}
		if (this->btns["dwn_ten"]->getState() == BTN_RELEASED)
		{
			this->selectedPopulation -= 10;

		}
		if (this->btns["dwn_one"]->getState() == BTN_RELEASED)
		{
			this->selectedPopulation -= 1;

		}
		if (this->btns["up_one"]->getState() == BTN_RELEASED)
		{
			this->selectedPopulation += 1;

		}
		if (this->btns["up_ten"]->getState() == BTN_RELEASED)
		{
			this->selectedPopulation += 10;

		}
		if (this->btns["up_hundred"]->getState() == BTN_RELEASED)
		{
			this->selectedPopulation += 100;

		}
		if (this->btns["up_thousand"]->getState() == BTN_RELEASED)
		{
			this->selectedPopulation += 1000;

		}

		if (this->selectedPopulation > this->maxPopulation)
		{
			this->selectedPopulation  = this->maxPopulation;
		}
		if (this->selectedPopulation < 0)
		{
			this->selectedPopulation = 0;
		}

		this->updateText();
	}
	void render()
	{
		for (auto& btn : this->btns)
		{
			btn.second->render();
		}
		this->parentWindow->draw(this->selectionDisplay);
		this->parentWindow->draw(this->selectionText);
	}
private:
	sf::Font& font;
	sf::RenderWindow* parentWindow;
	std::map<std::string, sfGUI::Button*> btns;
	sf::Color btnIdle;
	sf::Color btnHover;
	sf::Color btnActive;
	 
	sf::RectangleShape selectionDisplay;
	sf::Color displayColor;

	sf::Text selectionText;
	sf::Color txtColor;

	int maxPopulation;
	int selectedPopulation;
};

class simGui
{

public:
	simData* simulationData;

	sf::RectangleShape bounds;
	sf::Font font;

	//RESOLUTION
	sfGUI::Button* btn64, *btn128;
	sf::Text resLabel, resValue;

	//POPULATION
	PopulationSelector* populationSelector;
	sf::Text popLabel;

	//RESTART
	sfGUI::Button* restart;
	bool restartSimulation;

	void initFonts();
	void initResButtons();
	void initPopulationSelector();

	void initRestartButton();

	simGui(simData* data);
	~simGui();

	const bool getRestart() const;

	void masterUpdate();
	void updateResolutionButtons();
	void updatePopulationSelector();
	void updateRestartButton();

	void masterRender();
	void renderResolutionButtons();
	void renderPopulationSelector();
	void renderRestartButton();
};



#endif