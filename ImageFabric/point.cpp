#include "point.h"

#define DOUBLE 2
#define FRICTION 0.99f
#define GRAVITY 0.98f

#define POINT_RADIUS 0.5f
#define BOUNCINESS 0.0f

#include <iostream>

Point::Point() : Point(0.0f, 0.0f) { }

Point::Point(float x, float y) {
	position = sf::Vector2f(x, y);
	lastPosition = position;
    staticPoint = false;

    shape.setPosition(position);
    shape.setOrigin(sf::Vector2f(POINT_RADIUS, POINT_RADIUS));
    shape.setRadius(POINT_RADIUS);
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
    if (staticPoint) {
        return;
    }

    float velocityX = (position.x - lastPosition.x) * FRICTION;
    float velocityY = (position.y - lastPosition.y) * FRICTION;

    lastPosition.x = position.x;
    lastPosition.y = position.y;

    position.x += velocityX;
    position.y += velocityY + GRAVITY;

    constrain(deltaTime);

    shape.setPosition(position);
}

void Point::draw(sf::RenderWindow &window) {
    //shape.setRadius(10.0f);
    window.draw(shape);
}

void Point::setStatic(bool isStatic) {
    staticPoint = isStatic;
}

void Point::constrain(float deltaTime) {
    if (staticPoint) {
        return;
    }

    float velocityX = (position.x - lastPosition.x) * FRICTION;
    float velocityY = (position.y - lastPosition.y) * FRICTION;

    if (position.x > (640.0f - POINT_RADIUS)) {
        position.x = 640.0f - POINT_RADIUS;
        lastPosition.x += velocityX * BOUNCINESS;
    }
    else if (position.x < POINT_RADIUS) {
        position.x = POINT_RADIUS;
        lastPosition.x += velocityX * BOUNCINESS;
    }

    if (position.y > (480.0f - POINT_RADIUS)) {
        position.y = 480.0f - POINT_RADIUS;
        lastPosition.y += velocityY * BOUNCINESS;
    }
    else if (position.y < POINT_RADIUS) {
        position.y = POINT_RADIUS;
        lastPosition.y += velocityY * BOUNCINESS;
    }
}

float Point::distSqr(const Point &other) {
    const sf::Vector2f &otherPos = other.getPosition();

    return (position.x - otherPos.x) * (position.x - otherPos.x) +
           (position.y - otherPos.y) * (position.y - otherPos.y);
}

void Point::move(float deltaX, float deltaY, bool force) {
    if (!force && staticPoint) {
        return;
    }

    position.x += deltaX;
    position.y += deltaY;
}

void Point::setPosition(const sf::Vector2f &newPosition) {
    position = newPosition;
    lastPosition = newPosition;
}