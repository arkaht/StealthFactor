#include "DrawComponent.hpp"

#include <engine/gameplay/Entity.hpp>


namespace engine
{
	namespace gameplay
	{
		namespace components
		{
			DrawComponent::DrawComponent(graphics::ShapeList _shapeList, Entity& _owner)
				: shapeList(_shapeList), Component(_owner)
			{}
			

			void DrawComponent::draw(graphics::Manager& graphicsManager)
			{
				graphicsManager.draw(shapeList, owner.getTransform());
			}
		}
	}
}
