#pragma once

#include <engine/gameplay/Component.hpp>
#include <engine/graphics/ShapeList.hpp>
#include <engine/graphics/GraphicsManager.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace components
		{

			class DrawComponent : public Component
			{
			public:
				DrawComponent(graphics::ShapeList _shapeList, Entity& _owner);

				virtual void draw(graphics::Manager& graphicsManager);

			protected:
				graphics::ShapeList shapeList;
			};
		}
	}
}