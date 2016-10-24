#pragma once

#include <SFML/Graphics.hpp>

class Point
{
	private:
		sf::Vector2f position;
		sf::Vector2f lastPosition;
        sf::CircleShape shape;

	public:
		Point();
		Point(float x, float y);
        Point(float x, float y, float velocityX, float velocityY);
		const sf::Vector2f &getPosition() const;
		void update(float deltaTime);
        void draw(sf::RenderWindow &window);
        void move(float deltaX, float deltaY);
        float distSqr(const Point &other);
};

