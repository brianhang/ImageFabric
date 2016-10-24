#include "point.h"

#define DOUBLE 2
#define FRICTION 0.5f
#define GRAVITY 0.2f

#include <iostream>

Point::Point() : Point(0.0f, 0.0f) { }

Point::Point(float x, float y) {
	position = sf::Vector2f(x, y);
	lastPosition = position;

    shape.setPosition(position);
    shape.setOrigin(sf::Vector2f(8.0f, 8.0f));
    shape.setRadius(8.0f);
    shape.setFillColor(sf::Color::White);
}

Point::Point(float x, float y, float velocityX, float velocityY) :
Point(x, y) {
    lastPosition.x -= velocityX;
    lastPosition.y -= velocityY;
}

const sf::Vector2f &Point::getPosition() const {
	return position;
}

void Point::update(float deltaTime) {
    float velocityX = (position.x - lastPosition.x) * FRICTION;
    float velocityY = (position.y - lastPosition.y) * FRICTION;

    lastPosition.x = position.x;
    lastPosition.y = position.y;

    position.x += velocityX;
    position.y += velocityY + GRAVITY;

    if (position.x > 632.0f) {
        position.x = 632.0f;
        lastPosition.x += velocityX;
    } else if (position.x < 8.0f) {
        position.x = 8.0f;
        lastPosition.x += velocityX;
    }

    if (position.y > 472.0f) {
        position.y = 472.0f;
        lastPosition.y += velocityY;
    } else if (position.y < 8.0f) {
        position.y = 8.0f;
        lastPosition.y += velocityY;
    }

    shape.setPosition(position);
}

void Point::draw(sf::RenderWindow &window) {
    //shape.setRadius(10.0f);
    window.draw(shape);
}

float Point::distSqr(const Point &other) {
    const sf::Vector2f &otherPos = other.getPosition();

    return (position.x - otherPos.x) * (position.x - otherPos.x) +
           (position.y - otherPos.y) * (position.y - otherPos.y);
}

void Point::move(float deltaX, float deltaY) {
    position.x += deltaX;
    position.y += deltaY;
}