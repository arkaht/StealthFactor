#include "engine/Engine.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <pugixml/pugixml.hpp>
#include <SFML/System.hpp>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/graphics/GraphicsManager.hpp>
#include <engine/physics/PhysicsManager.hpp>
#include <engine/input/InputManager.hpp>

namespace engine
{
	Engine::Engine() 
	{
		gameplayManager = std::make_unique<gameplay::Manager>( *this );
		graphicsManager = std::make_unique<graphics::Manager>( *this );
		physicsManager = std::make_unique<physics::Manager>();
		inputManager = std::make_unique<input::Manager>( *this );
	}

	void Engine::loadConfiguration()
	{
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file("configuration.xml");

		if (result)
		{
			assert(!doc.empty());
			auto configuration = doc.first_child();
			startMap = configuration.child_value("start_map");
		}
		else
		{
			std::cerr << "Configuration parsed with errors." << std::endl;
			std::cerr << "Error description: " << result.description() << std::endl;
			std::cerr << "Error offset: " << result.offset << std::endl;
		}
	}

	void Engine::run()
	{
		running = true;

		//  init
		inputManager->init();
		gameplayManager->loadMap(startMap);

		//  bind window close
		graphicsManager->OnWindowClose.listen( "engine",
			std::bind( &Engine::exit, this )
		);

		//  game-loop
		sf::Clock clock;
		while (running)
		{
			deltaTime = clock.restart().asSeconds();

			//  update
			physicsManager->update();
			gameplayManager->update();
			inputManager->clear();
			graphicsManager->update();

			//  draw
			graphicsManager->draw();
		}

		//  release managers
		gameplayManager.reset( nullptr );
		graphicsManager.reset( nullptr );
		physicsManager.reset( nullptr );
		inputManager.reset( nullptr );
	}

	void Engine::exit()
	{
		//  close window and exit run loop
		graphicsManager->close();
		running = false;
	}
}
