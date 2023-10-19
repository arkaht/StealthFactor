#pragma once

#include <set>
#include <vector>
#include <ode/collision.h>
#include "engine/gameplay/components/PhysicComponent.hpp"

namespace engine
{
	namespace physics
	{
		class Manager
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

			void registerComponent(std::shared_ptr<gameplay::components::PhysicComponent> component);
			void unregisterComponent(std::shared_ptr<gameplay::components::PhysicComponent> component);

			void update();

			dSpaceID getSpaceId() const;

			std::set<dGeomID> getCollisionsWith(dGeomID object) const;

		private:
			dSpaceID spaceId;
			Collisions frameCollisions;

			std::vector<std::shared_ptr<gameplay::components::PhysicComponent>> components;

			static void nearCallback(void *data, dGeomID o1, dGeomID o2);
		};
	}
}
