#pragma once

#include <set>
#include <vector>
#include <ode/collision.h>
#include "engine/gameplay/components/PhysicComponent.hpp"

#include "engine/util/ComponentManager.hpp"

namespace engine
{
	namespace physics
	{
		class Manager : public util::ComponentManager<engine::gameplay::components::PhysicComponent>
		{
		public:
			struct Collision
			{
				dGeomID o1;
				dGeomID o2;

				Collision(dGeomID o1, dGeomID o2);
			};

			using Collisions = std::vector<Collision>;

			Manager();
			~Manager();

			void update();

			dSpaceID getSpaceId() const;

			std::set<dGeomID> getCollisionsWith(dGeomID object) const;

		private:
			dSpaceID spaceId;
			Collisions frameCollisions;

			static void nearCallback(void *data, dGeomID o1, dGeomID o2);
		};
	}
}
