#include "Character.hpp"

#include <engine/graphics/GraphicsManager.hpp>
#include <engine/physics/PhysicsManager.hpp>

#include "engine/Engine.hpp"

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			Character::Character( engine::Engine& engine )
				: Entity( engine )
			{
				collisionGeomId = dCreateBox(engine.getPhysicsManager().getSpaceId(), 0.f, 0.f, 0.f);
				dGeomSetData(collisionGeomId, this);
			}

			Character::~Character()
			{
				dGeomDestroy(collisionGeomId);
			}

			void Character::draw()
			{
				//engine.getGraphicsManager().draw(shapeList, getTransform());
			}
		}
	}
}
