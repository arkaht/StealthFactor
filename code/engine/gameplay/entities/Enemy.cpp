#include "Enemy.hpp"

#include <iostream>
#include <sstream>
#include <pugixml/pugixml.hpp>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/gameplay/entities/Player.hpp>

#include "engine/Engine.hpp"

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			Enemy::Enemy( engine::Engine& engine, const std::string& archetypeName )
				: Entity( engine )
			{
				loadArchetype( archetypeName );

				//  setup rendering
				createComponent<components::DrawComponent>(
					*this,
					engine.getGraphicsManager(),
					shapeList
				);
			}

			void Enemy::update()
			{
				//  get player
				auto weak_player = engine.getGameplayManager().getPlayer();
				std::shared_ptr<Player> player = weak_player.lock();
				if ( !player ) assert( false );

				if ( player->hasJustMoved() )
				{
					auto& playerPosition = player->getPosition();
					auto& myPosition = getPosition();

					auto offset = myPosition - playerPosition;
					offset /= gameplay::Manager::CELL_SIZE;
					float distance2 = offset.x * offset.x + offset.y * offset.y;
					if ( distance2 <= visionRadius * visionRadius )
					{
						if ( shootDelayCounter < shootDelay )
						{
							++shootDelayCounter;
						}
						else
						{
							engine.getGameplayManager().gameOver();
						}
					}
					else
					{
						shootDelayCounter = 0;
					}
				}
			}

			void Enemy::loadArchetype( const std::string& archetypeName )
			{
				std::stringstream filename;
				filename << "archetypes/" << archetypeName << ".xml";

				pugi::xml_document doc;
				pugi::xml_parse_result result = doc.load_file( filename.str().c_str() );

				if ( result )
				{
					assert( !doc.empty() );
					auto xmlArchetype = doc.first_child();

					std::string shapeListName = xmlArchetype.child_value( "shapelist" );
					assert( shapeList.load( shapeListName ) );

					visionRadius = std::stof( xmlArchetype.child_value( "vision_radius" ) );
					assert( visionRadius > 0.f );

					shootDelay = std::stoi( xmlArchetype.child_value( "shoot_delay" ) );
					assert( shootDelay >= 0 );
				}
				else
				{
					std::cerr << "Archetype [" << archetypeName << "] parsed with errors." << std::endl;
					std::cerr << "Error description: " << result.description() << std::endl;
					std::cerr << "Error offset: " << result.offset << std::endl;
				}
			}
		}
	}
}
