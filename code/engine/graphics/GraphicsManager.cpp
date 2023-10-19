#include "engine/graphics/GraphicsManager.hpp"

#include <cassert>
#include <engine/input/InputManager.hpp>
#include <engine/graphics/ShapeList.hpp>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/Engine.hpp>

namespace engine
{
	namespace graphics
	{
		Manager::Manager( engine::Engine& engine )
			: engine( engine )
		{
			window.create(
				sf::VideoMode {
					(unsigned int)WINDOW_WIDTH,
					(unsigned int)WINDOW_HEIGHT
				},
				"Stealth Factor"
			);
			window.setVerticalSyncEnabled( true );

			sf::View view( 
				sf::Vector2f { 0.f, 0.f }, 
				sf::Vector2f { (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT } 
			);
			window.setView( view );
		}

		void Manager::update()
		{
			//  polling window events
			sf::Event event;
			while ( window.pollEvent( event ) )
			{
				switch ( event.type )
				{
					//  window
					case sf::Event::GainedFocus:
						OnFocus.invoke( true );
						break;
					case sf::Event::LostFocus:
						OnFocus.invoke( false );
						break;
					case sf::Event::Closed:
						OnWindowClose.invoke();
						break;

					//  key inputs
					case sf::Event::KeyPressed:
						OnKeyPressed.invoke( event.key );
						break;
					case sf::Event::KeyReleased:
						OnKeyReleased.invoke( event.key );
						break;
				}
			}
		}

		void Manager::draw()
		{
			//  clear background
			clear();

			//  draw components
			for ( auto& component : components )
			{
				component->draw();
			}

			//  display on screen
			window.display();
		}

		void Manager::close()
		{
			window.close();
		}

		void Manager::setViewPosition( const sf::Vector2f& pos )
		{
			sf::View view {
				pos,
				sf::Vector2f{(float)WINDOW_WIDTH, (float)WINDOW_HEIGHT}
			};
			window.setView( view );
		}

		void Manager::drawShape( const ShapeList& shapeList, const sf::Transform& transform )
		{
			sf::RenderStates renderStates { transform };
			for ( auto shape : shapeList.getShapes() )
			{
				window.draw( *shape, renderStates );
			}
		}

		bool Manager::hasFocus() const
		{
			return window.hasFocus();
		}

		void Manager::clear()
		{
			window.clear( sf::Color::Black );
		}
	}
}
