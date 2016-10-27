#pragma once

#include <SFML/Graphics.hpp>

class Point
{
	private:
		sf::Vector2f position;
		sf::Vector2f lastPosition;
        sf::CircleShape shape;
        bool staticPoint;

	public:
		Point();
		Point(float x, float y);
        Point(float x, float y, float velocityX, float velocityY);
		const sf::Vector2f &getPosition() const;
		void update(float deltaTime);
        void draw(sf::RenderWindow &window);
        void move(float deltaX, float deltaY, bool force = false);
        void constrain(float deltaTime);
        void setStatic(bool isStatic);
        void setPosition(const sf::Vector2f &newPosition);
        float distSqr(const Point &other);
};

