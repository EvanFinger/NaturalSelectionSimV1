#ifndef SFML_GUI_H
#define SFML_GUI_H

//SFML INCLUDES
#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Network.hpp"

//Other includes
#include <iostream>
#include <cmath>

enum states { DEAD = -1, BTN_IDLE, BTN_HOVER, BTN_ACTIVE, BTN_RELEASED};

struct ColorPalette
		{
				//fill colors for rectangle shapes 
				//within the button class
			sf::Color ButtonIdle_fill = sf::Color::Red;
			sf::Color ButtonHover_fill = sf::Color::Green;
			sf::Color ButtonActive_fill = sf::Color::Blue;
			sf::Color ButtonToggled_fill = sf::Color::Yellow;
				//Outline colors for rectangles shapes
				//within the button class
			sf::Color ButtonIdle_outline= sf::Color::Transparent;
			sf::Color ButtonHover_outline = sf::Color::Transparent;
			sf::Color ButtonActive_outline = sf::Color::Transparent;
			sf::Color ButtonToggled_outline = sf::Color::Transparent;
				//text colors for text within the button class
			sf::Color ButtonIdle_txt = sf::Color::Transparent;
			sf::Color ButtonHover_txt = sf::Color::Transparent;
			sf::Color ButtonActive_txt = sf::Color::Transparent;
		};

namespace sfGUI
{
	class GuiElement
	{
	private:
		//GUI REQUIRED VARIABLES
		//PRIVATE FUNCTIONS
		//==============================
		//initializers
		void initVariables();

		//updaters
		

	protected:
		sf::RenderWindow* parentWindow;
		sf::Vector2f mousePositionView;
		short unsigned guiID;
		states state;
	public:
		GuiElement();
		virtual ~GuiElement();

		//PUBLIC FUNCTIONS
		//==============================
		//setters
		void setID(short unsigned id);

		//accessors
		short unsigned getID();
		short getState();
		//updaters
		virtual void update() = 0;
		void updateMousePosition();
		//renderers
		virtual void render() = 0;
	};

//==================================================//
//													//
// 				sfGUI ELEMENT : BUTTON			    //
//													//
//==================================================//
	class Button :
		public GuiElement
	{
	protected:
		//PROTECTED VARIABLES
		//references
		sf::Font& font;

		bool mouseDown;

		//GRAPHIC

		sf::RectangleShape boundingRect;
		sf::Text buttonText;

		ColorPalette boundingRectColors, textColors;

		sf::Texture buttonTexture;


		//PROTECTED FUNCTIONS
		//====================
		//initializers

	public:
		Button
		(
			sf::RenderWindow* parent_window, float pos_x, float pos_y,
			float size_x, float size_y, //bounding rect size
			sf::Font& font, unsigned short font_size, std::string text_string,
			unsigned short id
		);

		virtual ~Button
		(

		);

		//PUBLIC FUNCTIONS
		//====================
		//setters
		void setTexture(std::string filename);

		void setBoundingRectColors
		(
			sf::Color idle, sf::Color hover, sf::Color active,
			sf::Color outline_idle = sf::Color::Transparent, sf::Color outline_hover = sf::Color::Transparent, sf::Color outline_active = sf::Color::Transparent
		);

		void setTextColors(sf::Color idle, sf::Color hover, sf::Color active);

		void setString(std::string text);

		void setPosition(float x, float y);
		void kill();

		void live();
		//getters
		sf::RectangleShape* getBoundingRect();
		std::string getString();

		//updaters
			void update();
		//renderers
		void render();
		
	};

//==================================================//
//													//
// 		   sfGUI ELEMENT : TOGGLE BUTTON		    //
//													//
//==================================================//

	class ToggleButton :
		public GuiElement
	{
	private:
		sf::Font& font;

		bool toggled;
		bool mouseDown;

		//GRAPHIC

		sf::RectangleShape boundingRect;
		sf::Text buttonText;

		ColorPalette boundingRectColors, textColors;

		sf::Texture buttonTexture;
	public:

		ToggleButton
		(
			bool isToggled,
			sf::RenderWindow* parent_window, float pos_x, float pos_y,
			float size_x, float size_y, //bounding rect size
			sf::Font& font, unsigned short font_size, std::string text_string,
			unsigned short id
		);

		virtual ~ToggleButton
		(

		);

		//PUBLIC FUNCTIONS
		//====================
		//setters
		void setTexture(std::string filename);

		void setBoundingRectColors
		(
			sf::Color idle, sf::Color hover, sf::Color active,
			sf::Color outline_idle = sf::Color::Transparent, sf::Color outline_hover = sf::Color::Transparent, sf::Color outline_active = sf::Color::Transparent
		);

		void setTextColors(sf::Color idle, sf::Color hover, sf::Color active);

		void kill();

		void live();
		//getters
		sf::RectangleShape* getBoundingRect();
		const bool getToggled() const;

		//updaters
		void update();
		//renderers
		void render();
	};
//==================================================//
//													//
// 		   sfGUI ELEMENT : DROPDOWN MENU		    //
//													//
//==================================================//

	class DropdownMenu :
		public GuiElement
	{
	private:
		sf::Font& font;

		sfGUI::Button* active;
		sf::Color activeIdleColor;
		sf::Color activeHoverColor;
		sf::Color activeActiveColor;

		std::vector<sfGUI::Button*> list;
		sf::Color listIdleColor;
		sf::Color listHoverColor;
		sf::Color listActiveColor;

		bool showList;

		ColorPalette colors;
	public:
		DropdownMenu
		(
			sf::RenderWindow* window, float pos_x, float pos_y,
			float size_x, float size_y, float list_element_size_x, float list_element_size_y,
			sf::Font& font, std::string list[], unsigned num_elements, unsigned default_index = 0
		);
		virtual ~DropdownMenu();


		//Functions
		void setActiveElementColors
		(
			sf::Color idle,
			sf::Color hover,
			sf::Color active
		);

		void setListElementColors
		(
			sf::Color idle,
			sf::Color hover,
			sf::Color active
		);
		//getters
		const unsigned short getActiveID() const;

	void update();
	void render();
	};

//==================================================//
//													//
// 		   sfGUI ELEMENT : ARROW SELECTION		    //
//													//
//==================================================//
	class ArrowSelection :
		public GuiElement
	{
	private:
		sf::Font& font;
		sfGUI::Button* cycleLeft;
		sfGUI::Button* cycleRight;
		sf::Color btnIdle;
		sf::Color btnHover;
		sf::Color btnActive;

		sf::RectangleShape selectionDisplay;
		sf::Color displayColor;

		sf::Text selectionText;
		sf::Color txtColor;

		std::vector<std::string> list;
		int activeIndex;

	public:
		ArrowSelection
		(
			sf::RenderWindow* window, float x_pos, float y_pos,
			float arrow_button_width, float selection_display_width, float height,
			sf::Font& font, unsigned short font_size, std::string list[],
			unsigned short num_elements, unsigned short default_index = 0
		);
		virtual ~ArrowSelection();

		void setArrowColors
		(
			sf::Color idle,
			sf::Color hover,
			sf::Color active
		);

		void setDisplayColors(sf::Color bg, sf::Color txt);

		const int getActive() const;

		void updateText();

		void update();
		void render();
	};

//==================================================//
//													//
// 				 sfGUI ELEMENT : SLIDER		        //
//													//
//==================================================//
	class SmoothSlider :
		public GuiElement
	{
	private:
		sf::RectangleShape sliderTrack;
		sf::Color trackColor;
		sf::RectangleShape slider;
		sf::Color sliderIdle;
		sf::Color sliderHover;
		sf::Color sliderActive;

		bool active;

		sf::Text valueDisplay;
		sf::Font& font;
		std::string title;

		float sliderMax;
		float sliderValue;
		std::vector<float> snapValues;
		bool snapped;

	public:
		SmoothSlider
		(
			unsigned slider_max_value,
			sf::RenderWindow* window, float x_pos, float y_pos,
			float slider_track_length, float slider_length, float height,
			std::string slider_title,
			sf::Font& font, unsigned short font_size, float default_value
		);
		~SmoothSlider();

		void setTrackColor(sf::Color color);
		void setSliderColors(sf::Color idle, sf::Color hover, sf::Color active);

		float getSliderValue() const;
		void update();
		void render();
	};

//==================================================//
//													//
// 		    sfGUI ELEMENT : SNAP SLIDER		        //
//													//
//==================================================//
	class SnapSlider :
		public GuiElement
	{
	private:
		sf::RectangleShape sliderTrack;
		sf::Color trackColor;
		sf::RectangleShape slider;
		sf::Color sliderIdle;
		sf::Color sliderHover;
		sf::Color sliderActive;

		float originalSliderWidth;

		bool active;

		sf::Text valueDisplay;
		sf::Font& font;
		std::string title;

		float sliderValue;
		float sliderMax;
		std::vector<sf::RectangleShape> snapRects;
		unsigned short numSnaps;

	public:
		SnapSlider
		(
			unsigned slider_max_value,
			sf::RenderWindow* window, float x_pos, float y_pos,
			float slider_track_length, float slider_length, float height,
			unsigned short number_of_snaps, std::string slider_title,
			sf::Font& font, unsigned short font_size, float default_value
		);
		~SnapSlider();

		void setTrackColor(sf::Color color);
		void setSliderColors(sf::Color idle, sf::Color hover, sf::Color active);

		float getSliderValue() const;
		void update();
		void render();
	};

//==================================================//
//													//
// 		    sfGUI ELEMENT : SNAP SLIDER		        //
//													//
//==================================================//
	class textBox :
		public GuiElement
	{
	private:
		sf::RectangleShape boundingRect;
		sf::Text text;
		std::string input;
		sf::Font& font;
	public:
		textBox(sf::RenderWindow* window, float pos_x, float pos_y, float width, float height, sf::Font& font, unsigned font_size, std::string def_txt);
		~textBox();

		void update();
		void render();
	};
}






#endif
