#include "stdafx.h"
#include "simGui.h"

void simGui::initFonts()
{
	if (!this->font.loadFromFile("Fonts/TT Chocolates Trial Light.otf"))
	{
		std::cout << "FAILED TO LOAD FONT : simGUI.h" << "\n";
	}
}

void simGui::initResButtons()
{
	this->btn64 = new sfGUI::Button
	(
		this->simulationData->window, this->bounds.getPosition().x + this->bounds.getGlobalBounds().width / 2.f - 50.f, this->bounds.getPosition().y + 100.f,
		100.f, 50.f, 
		this->font, 20, "64 x 64", 0
	);
	this->btn64->setBoundingRectColors
	(
		sf::Color(139, 72, 199, 200), sf::Color(95, 49, 135, 255), sf::Color(41, 21, 59, 150)
	);
	

	this->btn128 = new sfGUI::Button
	(
		this->simulationData->window, this->bounds.getPosition().x + this->bounds.getGlobalBounds().width / 2.f - 50.f + this->btn64->getBoundingRect()->getGlobalBounds().width, this->bounds.getPosition().y + 100.f,
		100.f, 50.f,
		this->font, 20, "128 x 128", 0
	);
	this->btn128->setBoundingRectColors
	(
		sf::Color(139, 72, 199, 200), sf::Color(95, 49, 135, 255), sf::Color(41, 21, 59, 150)
	);


	this->resLabel.setFont(this->font);
	this->resLabel.setCharacterSize(30);
	this->resLabel.setFillColor(sf::Color::White);
	this->resLabel.setString("World Size : ");
	this->resLabel.setPosition
	(
		sf::Vector2f
		(
			this->bounds.getPosition().x + 100.f, this->bounds.getPosition().y + 105.f
		)
	);

	this->resValue.setFont(this->font);
	this->resValue.setCharacterSize(30);
	this->resValue.setFillColor(sf::Color::White);
	this->resValue.setString(std::to_string(this->simulationData->worldSize));
	this->resValue.setPosition
	(
		sf::Vector2f
		(
			this->resLabel.getPosition().x + this->resLabel.getGlobalBounds().width + 10.f, this->bounds.getPosition().y + 105.f
		)
	);
}

void simGui::initPopulationSelector()
{
	this->populationSelector = new PopulationSelector
	(
		this->simulationData->window, this->bounds.getPosition().x + 100.f, this->bounds.getPosition().y + 250.f,
		50.f, 100.f, 50.f, this->font, 20, 2000, 0
	);

	this->populationSelector->setArrowColors(sf::Color(139, 72, 199, 200), sf::Color(95, 49, 135, 255), sf::Color(41, 21, 59, 150));
	this->populationSelector->setDisplayColors(sf::Color(41, 21, 59, 150), sf::Color::White);

	this->popLabel.setFont(this->font);
	this->popLabel.setCharacterSize(30);
	this->popLabel.setFillColor(sf::Color::White);
	this->popLabel.setString("Set Population");
	this->popLabel.setPosition
	(
		sf::Vector2f
		(
			this->populationSelector->getPosition().x + this->populationSelector->getGlobalBounds().width / 2 - this->popLabel.getGlobalBounds().width / 2,
			this->populationSelector->getPosition().y - this->popLabel.getGlobalBounds().height - 10.f
		)
	);
}

void simGui::initRestartButton()
{
	this->restart = new sfGUI::Button
	(
		this->simulationData->window, this->bounds.getPosition().x + 800.f, 275.f, 50.f, 50.f, this->font, 20, "->", 0
	);
	this->restart->setBoundingRectColors
	(
		sf::Color(139, 72, 199, 200), sf::Color(95, 49, 135, 255), sf::Color(41, 21, 59, 150)
	);
}

simGui::simGui(simData* data)
{
	this->simulationData = data;
	this->restartSimulation = false;
	
	this->bounds.setPosition(sf::Vector2f(1004.f, 92.f));
	this->bounds.setSize(sf::Vector2f(900.f, 600.f));
	this->bounds.setFillColor(sf::Color::Transparent);
	this->bounds.setOutlineColor(sf::Color::White);
	this->bounds.setOutlineThickness(1);

	this->initFonts();
	this->initResButtons();
	this->initPopulationSelector();
	this->initRestartButton();

	

}

simGui::~simGui()
{
	delete this->btn64;
	delete this->btn128;
	delete this->restart;
}

const bool simGui::getRestart() const
{
	return this->restartSimulation;
}

void simGui::masterUpdate()
{
	this->updateResolutionButtons();
	this->updatePopulationSelector();
	this->updateRestartButton();
}

void simGui::updateResolutionButtons()
{
	this->btn64->update();
	if (this->btn64->getState() == BTN_RELEASED)
	{
		this->simulationData->worldSizeBuffer = 64;
	}
	this->btn128->update();
	if (this->btn128->getState() == BTN_RELEASED)
	{
		this->simulationData->worldSizeBuffer = 128;	
	}
	this->resValue.setString(std::to_string(this->simulationData->worldSize) + " <- " + std::to_string(this->simulationData->worldSizeBuffer));
}

void simGui::updatePopulationSelector()
{
	this->populationSelector->update();
	this->simulationData->populationBuffer = this->populationSelector->getPop();
}

void simGui::updateRestartButton()
{
	this->restart->update();
	if (this->restart->getState() == BTN_RELEASED)
		this->restartSimulation = true;
}

void simGui::masterRender()
{
	this->simulationData->window->draw(this->bounds);
	this->renderResolutionButtons();
	this->renderPopulationSelector();
	this->renderRestartButton();
	
}

void simGui::renderResolutionButtons()
{
	this->btn64->render();
	this->btn128->render();
	this->simulationData->window->draw(this->resLabel);
	this->simulationData->window->draw(this->resValue);
}

void simGui::renderPopulationSelector()
{
	this->populationSelector->render();
	this->simulationData->window->draw(this->popLabel);
}

void simGui::renderRestartButton()
{
	this->restart->render();
}


