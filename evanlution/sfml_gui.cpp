#include "sfml_gui.h"


void sfGUI::GuiElement::initVariables()
{
	this->parentWindow = nullptr;
	this->mousePositionView = sf::Vector2f(0.f, 0.f);
	this->guiID = NULL;
}



sfGUI::GuiElement::GuiElement()
{
	this->initVariables();
}

sfGUI::GuiElement::~GuiElement()
{
}

void sfGUI::GuiElement::update()
{
}

short sfGUI::GuiElement::getState()
{
	return this->state;
}

void sfGUI::GuiElement::updateMousePosition()
{
	if(this->state != DEAD)
		this->mousePositionView = this->parentWindow->mapPixelToCoords(sf::Mouse::getPosition(*this->parentWindow));
}

void sfGUI::GuiElement::setID(short unsigned id)
{
	this->guiID = id;
}

short unsigned sfGUI::GuiElement::getID()
{
	return this->guiID;
}



//==================================================//
//													//
// 				sfGUI ELEMENT : BUTTON			    //
//													//
//==================================================//

sfGUI::Button::Button
(	
	sf::RenderWindow* parent_window, float pos_x, float pos_y,
	float size_x, float size_y, //bounding rect size
	sf::Font& font, unsigned short font_size, std::string text_string,
	unsigned short id
)
	:font(font)
{
	this->parentWindow = parent_window;
	this->mousePositionView = sf::Vector2f(0.f, 0.f);
	this->guiID = id;
	this->state = BTN_IDLE;
	this->mouseDown = false;

	//BOUNDING RECT INIT
	this->boundingRect.setSize(sf::Vector2f(size_x, size_y));
	this->boundingRect.setPosition(sf::Vector2f(pos_x, pos_y));
	this->boundingRect.setFillColor(sf::Color::Transparent);
	this->boundingRect.setOutlineThickness(0);
	this->boundingRect.setOutlineColor(sf::Color::Transparent);
	
	//BUTTON TEXT INIT
	this->buttonText.setFont(this->font);
	this->buttonText.setCharacterSize(font_size);
	this->buttonText.setFillColor(sf::Color::White);
	this->buttonText.setString(text_string);
	this->buttonText.setPosition(
		this->boundingRect.getPosition().x + (this->boundingRect.getGlobalBounds().width / 2.f) - this->buttonText.getGlobalBounds().width / 2.f,
		this->boundingRect.getPosition().y + (this->boundingRect.getGlobalBounds().height / 2.f) - this->buttonText.getGlobalBounds().height
	);
}

sfGUI::Button::~Button()
{

}

void sfGUI::Button::setTexture(std::string filename)
{
	if (!this->buttonTexture.loadFromFile(filename))
		std::cout << "ERROR LOADING BUTTON TEXTURE : BUTTON " << this->guiID;

	this->boundingRect.setTexture(&this->buttonTexture);
}

void sfGUI::Button::setBoundingRectColors
(
	sf::Color idle, sf::Color hover, sf::Color active, 
	sf::Color outline_idle, sf::Color outline_hover, sf::Color outline_active
)
{
	this->boundingRectColors.ButtonIdle_fill = idle;
	this->boundingRectColors.ButtonHover_fill = hover;
	this->boundingRectColors.ButtonActive_fill = active;
	this->boundingRectColors.ButtonIdle_outline = outline_idle;
	this->boundingRectColors.ButtonHover_outline = outline_hover;
	this->boundingRectColors.ButtonActive_outline = outline_active;

	this->boundingRect.setFillColor(this->boundingRectColors.ButtonIdle_fill);
	this->boundingRect.setOutlineColor(this->boundingRectColors.ButtonIdle_outline);
}

void sfGUI::Button::setTextColors(sf::Color idle, sf::Color hover, sf::Color active)
{
	this->textColors.ButtonIdle_fill = idle;
	this->textColors.ButtonHover_fill = hover;
	this->textColors.ButtonActive_fill = active;

	this->buttonText.setFillColor(this->textColors.ButtonIdle_fill);
}

void sfGUI::Button::setString(std::string text)
{
	this->buttonText.setString(text);
}

void sfGUI::Button::kill()
{
	this->state = DEAD;
}

void sfGUI::Button::live()
{
	this->state = BTN_IDLE;
}

sf::RectangleShape* sfGUI::Button::getBoundingRect()
{
	return &this->boundingRect;
}

std::string sfGUI::Button::getString()
{
	return this->buttonText.getString();
}
void sfGUI::Button::update()
{
	if (this->state != DEAD)//BUTTON IS ALIVE
	{
		this->updateMousePosition();
		//std::cout << this->mousePositionView.x << " " << this->mousePositionView.y << "\n";
		this->state = BTN_IDLE;
		if (this->boundingRect.getGlobalBounds().contains(this->mousePositionView))//BUTTON HOVERED
		{
			this->state = BTN_HOVER;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->state = BTN_ACTIVE;
				this->mouseDown = true;
			}
			else if (this->mouseDown)
			{
				this->state = BTN_RELEASED;
				this->mouseDown = false;
				
			}
		}		
		switch (state)
			{
			case BTN_IDLE:
				this->boundingRect.setFillColor(this->boundingRectColors.ButtonIdle_fill);
				break;
			case BTN_HOVER:
				this->boundingRect.setFillColor(this->boundingRectColors.ButtonHover_fill);
				break;
			case BTN_ACTIVE:
				this->boundingRect.setFillColor(this->boundingRectColors.ButtonActive_fill);
				break;
			}
	}


	
}

void sfGUI::Button::setPosition(float x, float y)
{
	this->boundingRect.setPosition(x, y);
}



void sfGUI::Button::render()
{
	this->parentWindow->draw(this->boundingRect);
	this->parentWindow->draw(this->buttonText);
}


//==================================================//
//													//
// 		   sfGUI ELEMENT : TOGGLE BUTTON		    //
//													//
//==================================================//

sfGUI::ToggleButton::ToggleButton
(
	bool isToggled,
	sf::RenderWindow* parent_window, float pos_x, float pos_y,
	float size_x, float size_y,
	sf::Font& font, unsigned short font_size, std::string text_string, 
	unsigned short id)
	: font(font)
{
	this->toggled = isToggled;
	this->parentWindow = parent_window;
	this->mousePositionView = sf::Vector2f(0.f, 0.f);
	this->guiID = id;
	this->state = BTN_IDLE;
	this->mouseDown = false;

	//BOUNDING RECT INIT
	this->boundingRect.setSize(sf::Vector2f(size_x, size_y));
	this->boundingRect.setPosition(sf::Vector2f(pos_x, pos_y));
	this->boundingRect.setFillColor(sf::Color::Transparent);
	this->boundingRect.setOutlineThickness(0);
	this->boundingRect.setOutlineColor(sf::Color::Transparent);
	
	//BUTTON TEXT INIT
	this->buttonText.setFont(this->font);
	this->buttonText.setCharacterSize(font_size);
	this->buttonText.setFillColor(sf::Color::White);
	this->buttonText.setString(text_string);
	this->buttonText.setPosition(
		this->boundingRect.getPosition().x + (this->boundingRect.getGlobalBounds().width / 2.f) - this->buttonText.getGlobalBounds().width / 2.f,
		this->boundingRect.getPosition().y + (this->boundingRect.getGlobalBounds().height / 2.f) - this->buttonText.getGlobalBounds().height
	);
}

sfGUI::ToggleButton::~ToggleButton()
{

}

void sfGUI::ToggleButton::setTexture(std::string filename)
{
	if (!this->buttonTexture.loadFromFile(filename))
		std::cout << "ERROR LOADING BUTTON TEXTURE : BUTTON " << this->guiID;

	this->boundingRect.setTexture(&this->buttonTexture);
}

void sfGUI::ToggleButton::setBoundingRectColors
(
	sf::Color idle, sf::Color hover, sf::Color active,
	sf::Color outline_idle, sf::Color outline_hover, sf::Color outline_active
)
{
	this->boundingRectColors.ButtonIdle_fill = idle;
	this->boundingRectColors.ButtonHover_fill = hover;
	this->boundingRectColors.ButtonActive_fill = active;
	this->boundingRectColors.ButtonIdle_outline = outline_idle;
	this->boundingRectColors.ButtonHover_outline = outline_hover;
	this->boundingRectColors.ButtonActive_outline = outline_active;

	this->boundingRect.setFillColor(this->boundingRectColors.ButtonIdle_fill);
	this->boundingRect.setOutlineColor(this->boundingRectColors.ButtonIdle_outline);
}

void sfGUI::ToggleButton::setTextColors(sf::Color idle, sf::Color hover, sf::Color active)
{
	this->textColors.ButtonIdle_fill = idle;
	this->textColors.ButtonHover_fill = hover;
	this->textColors.ButtonActive_fill = active;

	this->buttonText.setFillColor(this->textColors.ButtonIdle_fill);
}

void sfGUI::ToggleButton::kill()
{
	this->state = DEAD;
}

void sfGUI::ToggleButton::live()
{
	this->state = BTN_IDLE;
}

sf::RectangleShape* sfGUI::ToggleButton::getBoundingRect()
{
	return &this->boundingRect;
}

const bool sfGUI::ToggleButton::getToggled() const
{
	return this->toggled;
}

void sfGUI::ToggleButton::update()
{
	if (this->state != DEAD)//BUTTON IS ALIVE
	{
		this->updateMousePosition();
		//std::cout << this->mousePositionView.x << " " << this->mousePositionView.y << "\n";
		this->state = BTN_IDLE;
		if (this->boundingRect.getGlobalBounds().contains(this->mousePositionView))//BUTTON HOVERED
		{
			this->state = BTN_HOVER;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->state = BTN_ACTIVE;
				
				
				this->mouseDown = true;
			}
			else if (this->mouseDown)
			{
				this->state = BTN_RELEASED;
				if (this->toggled)
					this->toggled = false;
				else
					this->toggled = true;
				this->mouseDown = false;

			}
		}
		switch (state)
		{
		case BTN_IDLE:
			this->boundingRect.setFillColor(this->boundingRectColors.ButtonIdle_fill);
			break;
		case BTN_HOVER:
			this->boundingRect.setFillColor(this->boundingRectColors.ButtonHover_fill);
			break;
		case BTN_ACTIVE:
			this->boundingRect.setFillColor(this->boundingRectColors.ButtonActive_fill);
			break;
		}

		if (toggled)
		{
			this->boundingRect.setFillColor(sf::Color(boundingRect.getFillColor().r * 0.5, boundingRect.getFillColor().g * 0.5, boundingRect.getFillColor().b * 0.5, boundingRect.getFillColor().a));
		}
	}
}

void sfGUI::ToggleButton::render()
{
	this->parentWindow->draw(this->boundingRect);
	this->parentWindow->draw(this->buttonText);
}

//==================================================//
//													//
// 		   sfGUI ELEMENT : DROP DOWN MENU		    //
//													//
//==================================================//



sfGUI::DropdownMenu::DropdownMenu
(
	sf::RenderWindow* window, float pos_x, float pos_y,
	float size_x, float size_y, float list_element_size_x, float list_element_size_y,
	sf::Font& font, std::string list[], unsigned num_elements, unsigned default_index
)
	: font(font)
{
	this->parentWindow = window;

	this->active = new Button
	(
		this->parentWindow, pos_x, pos_y,
		size_x, size_y, this->font, 10, list[default_index],
		0
	);

	this->active->setBoundingRectColors(sf::Color::Red, sf::Color::Green, sf::Color::Blue);

	for (size_t i = 0; i < num_elements; i++)
	{
		this->list.push_back
		(
			new Button
			(
				this->parentWindow, pos_x, static_cast<int>(i) * list_element_size_y + size_y,
				list_element_size_x, list_element_size_y,
				this->font, 10, list[i],
				static_cast<unsigned>(i)
			)
		);

		this->list[i]->setBoundingRectColors(sf::Color::Red, sf::Color::Green, sf::Color::Blue);
	}
}

sfGUI::DropdownMenu::~DropdownMenu()
{

}

void sfGUI::DropdownMenu::setActiveElementColors(sf::Color idle, sf::Color hover, sf::Color active)
{
	this->activeIdleColor = idle; 
	this->activeHoverColor = hover;
	this->activeActiveColor = active;

	this->active->setBoundingRectColors
	(this->activeIdleColor, this->activeHoverColor, this->activeActiveColor);
}

void sfGUI::DropdownMenu::setListElementColors(sf::Color idle, sf::Color hover, sf::Color active)
{
	this->listIdleColor = idle;
	this->listHoverColor = hover;
	this->listActiveColor = active;

	for (auto it : this->list)
	{
		it->setBoundingRectColors
		(this->listIdleColor, this->listHoverColor, this->listActiveColor);
	}
}

const unsigned short sfGUI::DropdownMenu::getActiveID() const
{
	return this->active->getID();
}

void sfGUI::DropdownMenu::update()
{
	this->active->update();
	if (this->active->getState() == BTN_RELEASED && !showList)
		this->showList = true;
	else if (this->active->getState() == BTN_RELEASED)
		this->showList = false;

	if (this->showList)
	{
		for (auto iterator : this->list)
		{
			iterator->update();

			if (iterator->getState() == BTN_ACTIVE)
			{
				this->showList = false;
				this->active->setString(iterator->getString());
				this->active->setID(iterator->getID());
			}
		}
	}
}

void sfGUI::DropdownMenu::render()
{
	this->active->render();
	if (this->showList)
	{
		for (size_t i = 0; i < this->list.size(); i++)
		{
			this->list[i]->render();
		}
	}
}

//==================================================//
//													//
// 		   sfGUI ELEMENT : ARROW SELECTION		    //
//													//
//==================================================//

sfGUI::ArrowSelection::ArrowSelection
(
	sf::RenderWindow* window, float x_pos, float y_pos, 
	float arrow_button_width, float selection_display_width, float height, 
	sf::Font& font, unsigned short font_size, std::string list[], 
	unsigned short num_elements, unsigned short default_index)
	:font(font)
{
	this->parentWindow = window;
	for (int i = 0; i < num_elements; i++)
	{
		this->list.push_back(list[i]);
	}

	this->activeIndex = default_index;

	this->cycleLeft = new sfGUI::Button
	(
		this->parentWindow, x_pos, y_pos,
		arrow_button_width, height,
		this->font, font_size, "<-",
		0
	);

	this->cycleLeft->setBoundingRectColors
	(
		sf::Color::Red, sf::Color::Green, sf::Color::Blue
	);

	this->selectionDisplay.setPosition
	(
		sf::Vector2f
		(
			x_pos + this->cycleLeft->getBoundingRect()->getGlobalBounds().width,
			y_pos
		)
	);
	this->selectionDisplay.setSize
	(
		sf::Vector2f
		(
			selection_display_width,
			height
		)
	);
	this->selectionDisplay.setFillColor(sf::Color::Black);

	this->selectionText.setFont(this->font);
	this->selectionText.setCharacterSize(font_size);
	this->selectionText.setString(list[this->activeIndex]);
	this->selectionText.setPosition
	(
		sf::Vector2f
		(
			this->selectionDisplay.getPosition().x + this->selectionDisplay.getGlobalBounds().width / 2.f - this->selectionText.getGlobalBounds().width / 2.f,
			this->selectionDisplay.getPosition().y + this->selectionDisplay.getGlobalBounds().height / 2.f - this->selectionText.getGlobalBounds().height / 2.f
		)
		
	);

	this->cycleRight = new sfGUI::Button
	(
		this->parentWindow, x_pos + arrow_button_width + selection_display_width, y_pos,
		arrow_button_width, height,
		this->font, font_size, "->",
		0
	);

	this->cycleRight->setBoundingRectColors
	(
		sf::Color::Red, sf::Color::Green, sf::Color::Blue
	);
}

sfGUI::ArrowSelection::~ArrowSelection()
{
}

void sfGUI::ArrowSelection::setArrowColors(sf::Color idle, sf::Color hover, sf::Color active)
{
	this->btnIdle = idle;
	this->btnHover = hover;
	this->btnActive = active;

	this->cycleLeft->setBoundingRectColors
	(
		this->btnIdle, this->btnHover, this->btnActive
	);
	this->cycleRight->setBoundingRectColors
	(
		this->btnIdle, this->btnHover, this->btnActive
	);
}

void sfGUI::ArrowSelection::setDisplayColors(sf::Color bg, sf::Color txt)
{
	this->displayColor = bg;
	this->txtColor = txt;

	this->selectionDisplay.setFillColor(this->displayColor);
	this->selectionText.setFillColor(this->txtColor);
}



const int sfGUI::ArrowSelection::getActive() const
{
	return this->activeIndex;
}

void sfGUI::ArrowSelection::updateText()
{
	this->selectionText.setString(this->list[this->activeIndex]);
	this->selectionText.setPosition
	(
		sf::Vector2f
		(
			this->selectionDisplay.getPosition().x + this->selectionDisplay.getGlobalBounds().width / 2.f - this->selectionText.getGlobalBounds().width / 2.f,
			this->selectionDisplay.getPosition().y + this->selectionDisplay.getGlobalBounds().height / 2.f - this->selectionText.getGlobalBounds().height / 2.f
		)

	);
}

void sfGUI::ArrowSelection::update()
{
	this->cycleLeft->update();
	if (this->cycleLeft->getState() == BTN_RELEASED)
	{
		if (this->activeIndex > 0)
			this->activeIndex -= 1;
		else
			this->activeIndex = this->list.size() - 1;
	}

	this->cycleRight->update();
	if (this->cycleRight->getState() == BTN_RELEASED)
	{
		if (this->activeIndex < this->list.size() - 1)
			this->activeIndex += 1;
		else
			this->activeIndex = 0;
	}
	
	this->updateText();

}

void sfGUI::ArrowSelection::render()
{
	this->cycleLeft->render();
	this->parentWindow->draw(this->selectionDisplay);
	this->parentWindow->draw(this->selectionText);
	this->cycleRight->render();
}

//==================================================//
//													//
// 				 sfGUI ELEMENT : SLIDER		        //
//													//
//==================================================//

sfGUI::SmoothSlider::SmoothSlider
(
	unsigned slider_max_value,
	sf::RenderWindow* window, float x_pos, float y_pos,
	float slider_track_length, float slider_length, float height,
	std::string slider_title,
	sf::Font& font, unsigned short font_size, float default_value
)
	:font(font)
{
	this->sliderMax = slider_max_value;
	this->snapped = false;
	this->active = false;

	this->title = slider_title;
	this->parentWindow = window;
	this->sliderValue = default_value;
	this->sliderTrack.setPosition
	(
		sf::Vector2f
		(
			x_pos,
			y_pos
		)
	);
	this->sliderTrack.setSize
	(
		sf::Vector2f
		(
			slider_track_length,
			height
		)
	);
	this->sliderTrack.setFillColor(sf::Color::White);

	this->slider.setPosition(
		this->sliderTrack.getPosition().x + default_value,
		y_pos
	);
	this->slider.setSize
	(
		sf::Vector2f
		(
			slider_length, height
		)
	);
	this->slider.setFillColor(sf::Color::Red);

	this->valueDisplay.setFont(this->font);
	this->valueDisplay.setCharacterSize(font_size);
	this->valueDisplay.setFillColor(sf::Color::White);
	this->valueDisplay.setString(std::to_string(default_value));
	this->valueDisplay.setPosition
	(
		sf::Vector2f
		(
			x_pos, y_pos - 2*  this->valueDisplay.getGlobalBounds().height
		)
	);
}

sfGUI::SmoothSlider::~SmoothSlider()
{
}

void sfGUI::SmoothSlider::setTrackColor(sf::Color color)
{
	this->trackColor = color;
}

void sfGUI::SmoothSlider::setSliderColors(sf::Color idle, sf::Color hover, sf::Color active)
{
	this->sliderIdle = idle;
	this->sliderHover = hover;
	this->sliderActive = active;
}

float sfGUI::SmoothSlider::getSliderValue() const
{
	return this->sliderValue;
}

void sfGUI::SmoothSlider::update()
{
	this->updateMousePosition();
	this->slider.setFillColor(this->sliderIdle);
	if (this->sliderTrack.getGlobalBounds().contains(this->mousePositionView))
	{
		this->slider.setFillColor(this->sliderHover);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->active = true;
				
			}
	}
	

	if(active)
	{
		this->slider.setFillColor(this->sliderActive);
		
		for (auto it : this->snapValues)
		{
			if (this->sliderValue == it)
			{
				this->snapped = true;
				if (this->mousePositionView.x < this->slider.getPosition().x || (this->mousePositionView.x > this->slider.getPosition().x + this->slider.getGlobalBounds().width))
				{
					this->snapped = false;
					this->slider.setPosition
					(
						this->mousePositionView.x - this->slider.getSize().x / 2,
						this->slider.getPosition().y
					);
				}
			}
			
			
		}
		if(!snapped)
		{
			this->slider.setPosition
			(
				this->mousePositionView.x - this->slider.getSize().x / 2,
				this->slider.getPosition().y
			);
		}


		if (this->slider.getPosition().x < this->sliderTrack.getPosition().x)
			this->slider.setPosition(this->sliderTrack.getPosition().x, this->slider.getPosition().y);
		else if (this->slider.getPosition().x > this->sliderTrack.getPosition().x + this->sliderTrack.getGlobalBounds().width - this->slider.getGlobalBounds().width)
			this->slider.setPosition(this->sliderTrack.getPosition().x + this->sliderTrack.getGlobalBounds().width - this->slider.getGlobalBounds().width, this->slider.getPosition().y);

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->active = false;
	}
	this->sliderValue = (this->slider.getPosition().x - this->sliderTrack.getPosition().x) / (this->sliderTrack.getGlobalBounds().width - this->slider.getGlobalBounds().width);
	this->valueDisplay.setString(this->title + ": " + std::to_string(static_cast<int>(this->sliderValue * this->sliderMax)));
}

void sfGUI::SmoothSlider::render()
{
	this->parentWindow->draw(this->sliderTrack);
	this->parentWindow->draw(this->slider);
	this->parentWindow->draw(this->valueDisplay);
}

//==================================================//
//													//
// 			sfGUI ELEMENT : SNAP SLIDER		        //
//													//
//==================================================//

sfGUI::SnapSlider::SnapSlider
(
	unsigned slider_max_value,
	sf::RenderWindow* window, float x_pos, float y_pos,
	float slider_track_length, float slider_length, float height,
	unsigned short number_of_snaps, std::string slider_title,
	sf::Font& font, unsigned short font_size, float default_value
)
	:font(font)
{
	this->sliderMax = slider_max_value;
	this->parentWindow = window;
	this->sliderValue = NULL;
	this->originalSliderWidth = slider_length;
	this->numSnaps = number_of_snaps;
	this->active = false;
	this->snapRects.resize(number_of_snaps);
	for (size_t i = 0; i < snapRects.size(); i++)
	{
		int rectSize = slider_track_length / (numSnaps - 1);
		if (i == 0)
		{
			snapRects[i].setSize(sf::Vector2f(rectSize / 2.f, this->parentWindow->getSize().y));
			snapRects[i].setPosition(x_pos, 0.f);
		}
		else if (i > 0 && i < (this->snapRects.size() - 1))
		{
			snapRects[i].setSize(sf::Vector2f(rectSize, this->parentWindow->getSize().y));
			snapRects[i].setPosition(snapRects[i - 1].getPosition().x + snapRects[i - 1].getGlobalBounds().width, 0.f);
		}
		else
		{
			snapRects[i].setSize(sf::Vector2f(rectSize / 2.f, this->parentWindow->getSize().y));
			snapRects[i].setPosition(snapRects[i - 1].getPosition().x + snapRects[i - 1].getGlobalBounds().width, 0.f);
		}

		snapRects[i].setFillColor(sf::Color::Black);
		snapRects[i].setOutlineColor(sf::Color::White);
		snapRects[i].setOutlineThickness(-1);
	}





	
	this->sliderTrack.setPosition
	(
		sf::Vector2f
		(
			x_pos,
			y_pos
		)
	);
	this->sliderTrack.setSize
	(
		sf::Vector2f
		(
			slider_track_length,
			height
		)
	);
	this->sliderTrack.setFillColor(sf::Color::White);

	this->slider.setPosition(
		this->sliderTrack.getPosition().x + default_value,
		y_pos
	);
	this->slider.setSize
	(
		sf::Vector2f
		(
			slider_length, height
		)
	);
	this->slider.setFillColor(sf::Color::Red);

	this->valueDisplay.setFont(this->font);
	this->valueDisplay.setCharacterSize(font_size);
	this->valueDisplay.setFillColor(sf::Color::White);
	this->title = slider_title;
	this->valueDisplay.setString(slider_title + ": " + std::to_string(default_value));
	this->valueDisplay.setPosition
	(
		sf::Vector2f
		(
			x_pos, y_pos - 2 * this->valueDisplay.getGlobalBounds().height
		)
	);
}

sfGUI::SnapSlider::~SnapSlider()
{
}

void sfGUI::SnapSlider::setTrackColor(sf::Color color)
{
	this->trackColor = color;
}

void sfGUI::SnapSlider::setSliderColors(sf::Color idle, sf::Color hover, sf::Color active)
{
	this->sliderIdle = idle;
	this->sliderHover = hover;
	this->sliderActive = active;
}

float sfGUI::SnapSlider::getSliderValue() const
{
	return this->sliderValue;
}

void sfGUI::SnapSlider::update()
{
	this->updateMousePosition();
	this->slider.setFillColor(this->sliderIdle);
	if (this->sliderTrack.getGlobalBounds().contains(this->mousePositionView))
	{
		this->slider.setFillColor(this->sliderHover);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->active = true;

		}
	}


	if (active)
	{
		this->slider.setFillColor(this->sliderActive);
		for (size_t i = 0; i < this->snapRects.size(); i++)
		{
			if (this->snapRects[i].getGlobalBounds().contains(this->mousePositionView))
			{
				if (i == 0)
				{
					this->slider.setSize(sf::Vector2f(this->originalSliderWidth / 2.f, this->slider.getGlobalBounds().height));
					this->slider.setPosition(0.f, this->slider.getPosition().y);
					this->sliderValue = (1.f / (numSnaps - 1) * i);
				}
				else if (i > 0 && i < (this->snapRects.size() - 1))
				{
					this->slider.setSize(sf::Vector2f(this->originalSliderWidth, this->slider.getGlobalBounds().height));
					this->slider.setPosition((this->snapRects[i].getPosition().x + this->snapRects[i].getGlobalBounds().width / 2.f) - this->slider.getGlobalBounds().width / 2.f, this->slider.getPosition().y);
					this->sliderValue = (1.f / (numSnaps - 1) * i);
				}
				else
				{
					this->slider.setSize(sf::Vector2f(this->originalSliderWidth / 2.f, this->slider.getGlobalBounds().height));
					this->slider.setPosition(this->sliderTrack.getPosition().x + this->sliderTrack.getGlobalBounds().width - this->slider.getGlobalBounds().width, this->slider.getPosition().y);
					this->sliderValue = (1.f / (numSnaps - 1) * i);
				}
			}
		}
		}

		if (this->slider.getPosition().x < this->sliderTrack.getPosition().x)
			this->slider.setPosition(this->sliderTrack.getPosition().x, this->slider.getPosition().y);
		else if (this->slider.getPosition().x > this->sliderTrack.getPosition().x + this->sliderTrack.getGlobalBounds().width - this->slider.getGlobalBounds().width)
			this->slider.setPosition(this->sliderTrack.getPosition().x + this->sliderTrack.getGlobalBounds().width - this->slider.getGlobalBounds().width, this->slider.getPosition().y);

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->active = false;
	
	this->valueDisplay.setString(this->title + ": " + std::to_string(static_cast<int>(this->sliderValue * this->sliderMax)));
}

void sfGUI::SnapSlider::render()
{
	/*for (auto it : this->snapRects)
	{
		this->parentWindow->draw(it);
	}*/
	this->parentWindow->draw(this->sliderTrack);
	this->parentWindow->draw(this->slider);
	
	this->parentWindow->draw(this->valueDisplay);
}

sfGUI::textBox::textBox(sf::RenderWindow* window, float pos_x, float pos_y, float width, float height, sf::Font& font, unsigned font_size, std::string def_txt)
	:font(font)
{
	this->parentWindow = window;
	this->input = "";
	this->boundingRect.setSize(sf::Vector2f(width, height));
	this->boundingRect.setPosition(sf::Vector2f(pos_x, pos_y));
	this->boundingRect.setFillColor(sf::Color::White);
	this->boundingRect.setOutlineColor(sf::Color::Black);
	this->boundingRect.setOutlineThickness(1);

	this->text.setFont(this->font);
	this->text.setCharacterSize(font_size);
	this->text.setString(def_txt);
	this-> text.setFillColor(sf::Color::Black);
	this->text.setPosition(pos_x + 5.f, pos_y + 5.f);
}

sfGUI::textBox::~textBox()
{
}

void sfGUI::textBox::update()
{
	sf::Event e;
	while (this->parentWindow->pollEvent(e))
	{
		if (e.type == sf::Event::KeyPressed) {
			if (e.type == sf::Event::TextEntered) {
				if (e.text.unicode < 128) {
					input += static_cast<char>(e.text.unicode);
					this->text.setFillColor(sf::Color::White);
					this->text.setString(input);
				}
			}
		}
	}
}

void sfGUI::textBox::render()
{
	this->parentWindow->draw(this->boundingRect);
	this->parentWindow->draw(this->text);
}
