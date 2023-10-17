#include "engine/gameplay/GameplayManager.hpp"

#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <pugixml/pugixml.hpp>
#include <engine/Engine.hpp>
#include <engine/gameplay/entities/Enemy.hpp>
#include <engine/gameplay/entities/Player.hpp>
#include <engine/gameplay/entities/Target.hpp>

namespace engine
{
	namespace gameplay
	{
		const float Manager::CELL_SIZE = 50.f;

		Manager::Manager( engine::Engine& engine )
			: engine( engine )
		{}

		Manager::~Manager()
		{
			entitiesContainer.clear();
		}

		void Manager::update()
		{
			for ( auto& entity : entitiesContainer )
			{
				entity->update();
			}

			preventMapCompletion = false;
			if ( nextMapRequested && !nextMapName.empty() )
			{
				nextMapRequested = false;
				loadMap( nextMapName );
			}
		}

		void Manager::draw()
		{
			for ( auto& entity : entitiesContainer )
			{
				entity->draw();
			}
		}

		void Manager::gameOver()
		{
			std::cout << "Game over" << std::endl;
			scheduleLoadMap( currentMapName );
		}

		sf::Vector2f Manager::getViewCenter() const
		{
			return sf::Vector2f { columns * ( CELL_SIZE / 2.f ), rows * ( CELL_SIZE / 2.f ) };
		}

		void Manager::loadMap( const std::string& mapName )
		{
			//  clear entities
			entitiesContainer.clear();

			//  read document
			std::string filename = "maps/" + mapName + ".xml";
			pugi::xml_document doc;
			pugi::xml_parse_result result = doc.load_file( filename.c_str() );
			if ( !result )
			{
				std::cerr << "Map [" << mapName << "] parsed with errors." << std::endl;
				std::cerr << "Error description: " << result.description() << std::endl;
				std::cerr << "Error offset: " << result.offset << std::endl;
				return;
			}

			assert( !doc.empty() );
			auto xmlMap = doc.first_child();

			rows = std::stoi( xmlMap.child_value( "rows" ) );
			assert( rows >= 0 );

			columns = std::stoi( xmlMap.child_value( "columns" ) );
			assert( columns >= 0 );

			for ( auto& xmlElement : xmlMap.child( "elements" ).children() )
			{
				if ( !std::strcmp( xmlElement.name(), "enemy" ) )
				{
					int row = std::stoi( xmlElement.child_value( "row" ) );
					assert( row >= 0 && row < rows );

					int column = std::stoi( xmlElement.child_value( "column" ) );
					assert( column >= 0 && column < columns );

					std::string archetypeName = xmlElement.child_value( "archetype" );

					auto entity = std::make_shared<entities::Enemy>( engine, archetypeName );
					entity->setPosition( sf::Vector2f { ( column + 0.5f ) * CELL_SIZE, ( row + 0.5f ) * CELL_SIZE } );

					entitiesContainer.insert( entity );
				}

				if ( !std::strcmp( xmlElement.name(), "player" ) )
				{
					int row = std::stoi( xmlElement.child_value( "row" ) );
					assert( row >= 0 && row < rows );

					int column = std::stoi( xmlElement.child_value( "column" ) );
					assert( column >= 0 && column < columns );

					auto entity = std::make_shared<entities::Player>( engine );
					entity->setPosition( sf::Vector2f { ( column + 0.5f ) * CELL_SIZE, ( row + 0.5f ) * CELL_SIZE } );

					entitiesContainer.insert( entity );
					playerEntity = entity;
				}

				if ( !std::strcmp( xmlElement.name(), "target" ) )
				{
					int row = std::stoi( xmlElement.child_value( "row" ) );
					assert( row >= 0 && row < rows );

					int column = std::stoi( xmlElement.child_value( "column" ) );
					assert( column >= 0 && column < columns );

					auto entity = std::make_shared<entities::Target>( engine );
					entity->setPosition( sf::Vector2f { ( column + 0.5f ) * CELL_SIZE, ( row + 0.5f ) * CELL_SIZE } );

					entitiesContainer.insert( entity );
				}
			}

			currentMapName = mapName;
			nextMapName = xmlMap.child_value( "next_map" );

			//  set camera view
			engine.getGraphicsManager().setViewPosition( getViewCenter() );

			// JIRA-1337: Map is skipped.
			// This prevents the map to be completed during the first frame. I don't know why this happens.
			preventMapCompletion = true;
		}

		void Manager::scheduleLoadMap( const std::string& map_name )
		{
			if ( !preventMapCompletion )
			{
				nextMapRequested = true;
				nextMapName = map_name;
			}
		}

		void Manager::scheduleLoadNextMap()
		{
			scheduleLoadMap( nextMapName );
		}
	}
}
