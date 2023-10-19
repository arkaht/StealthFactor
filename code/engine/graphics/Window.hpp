#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Window/Event.hpp>

#include "engine/util/Event.hpp"

namespace engine
{
	namespace graphics
	{
		class Window
		{
		public:
			/*
			 *  Event when window gained or lost focus
			 *  Parameters:
			 *  -  bool has_focus: Either the window gained or lost focus
			 */
			util::Event<bool> OnFocus;

			/*
			 *  Event when key is pressed
			 *  Parameters:
			 *	-  sf::Event::KeyEvent key: Key pressed
			 */
			util::Event<const sf::Event::KeyEvent&> OnKeyPressed;

			/*
			 *  Event when key is released
			 *  Parameters:
			 *	-  sf::Event::KeyEvent key: Key released
			 */
			util::Event<const sf::Event::KeyEvent&> OnKeyReleased;

			/*
			 *  Event when the window is about to close, most likely by user input
			 *  Parameters: none
			 */
			util::Event<> OnWindowClose;



			Window(sf::Int16 width, sf::Int16 height, std::string name);

			void pollEvents();
			void display();
			void clear();

			void setView(sf::View view);
			void draw(const sf::Drawable& shape, sf::RenderStates& render_states);

			bool hasFocus() const;
			void close();

		private:
			sf::RenderWindow window;
		};
	}
}

