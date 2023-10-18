#include "Target.hpp"

#include <engine/gameplay/GameplayManager.hpp>
#include <engine/graphics/GraphicsManager.hpp>
#include <engine/physics/PhysicsManager.hpp>

#include "engine/Engine.hpp"

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			Target::Target( engine::Engine& engine )
				: Entity( engine )
			{
				shapeList.load("target");

				collisionGeomId = dCreateBox( 
					engine.getPhysicsManager().getSpaceId(),
					gameplay::Manager::CELL_SIZE * 0.9f,
					gameplay::Manager::CELL_SIZE * 0.9f, 
					1.f
				);
				dGeomSetData(collisionGeomId, this);
			}

			Target::~Target()
			{
				dGeomDestroy(collisionGeomId);
			}

			void Target::update()
			{
				auto &position = getPosition();
				dGeomSetPosition(collisionGeomId, position.x, position.y, 0);
			}

			void Target::draw()
			{
				engine.getGraphicsManager().draw(shapeList, getTransform());
			}
		}
	}
}