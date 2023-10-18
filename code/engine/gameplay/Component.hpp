#pragma once

namespace engine
{
	namespace gameplay
	{
		class Entity;


		class Component
		{
		public:
			Component(Entity& _owner) : owner(_owner) {}


		protected:
			Entity& owner;
		};
	}
}