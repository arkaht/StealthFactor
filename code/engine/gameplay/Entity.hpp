#pragma once

#include <SFML/Graphics/Transform.hpp>

namespace engine
{
	class Engine;
}

namespace engine
{
	namespace gameplay
	{
		class Entity
		{
		public:
			Entity( engine::Engine& engine );
			virtual ~Entity() = default;

			virtual void update() = 0;
			virtual void draw() = 0;

			const sf::Vector2f &getPosition() const;
			void setPosition(const sf::Vector2f &newPosition);

			float getRotation() const;
			void setRotation(float newRotation);

			const sf::Transform &getTransform() const;

		protected:
			engine::Engine& engine;

		private:
			sf::Vector2f _position{};
			float _rotation{ 0.f };
			sf::Transform _transform;

			void updateTransform();
		};
	}
}
