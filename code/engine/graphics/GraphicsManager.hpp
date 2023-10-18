#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Window/Event.hpp>
#include "engine/util/Event.hpp"
#include "engine/gameplay/components/DrawComponent.hpp"

namespace engine
{
	class Engine;

	namespace graphics
	{
		class ShapeList;

		class Manager
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

			Manager( engine::Engine& engine );

			void registerComponent( std::shared_ptr<gameplay::components::DrawComponent> component );
			void unregisterComponent( std::shared_ptr<gameplay::components::DrawComponent> component );
			
			void update();
			void draw();
			void close();

			void setViewPosition( const sf::Vector2f& pos );

			void drawShape(const ShapeList &shapeList, const sf::Transform &transform);

			bool hasFocus() const;

		private:
			void clear();

			std::vector<std::shared_ptr<gameplay::components::DrawComponent>> components;
			sf::RenderWindow window;

			static const sf::Int16 WINDOW_WIDTH = 800;
			static const sf::Int16 WINDOW_HEIGHT = 600;

			engine::Engine& engine;
		};
	}
}
