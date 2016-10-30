#include "point.h"

// Constants for how points move.
#define FRICTION 0.95f
#define GRAVITY 0.5f
#define BOUNCINESS 0.0f

// Margins for the walls.
#define POINT_RADIUS 0.0f

// Empty constructor for the Point.
Point::Point() : Point(0.0f, 0.0f) { }

// Constructor that specifies the initial position of the point.
Point::Point(float x, float y) {
    position = sf::Vector2f(x, y);
    lastPosition = position;
    staticPoint = false;
}

// Constructor that specifies the initial position and velocity of the point.
Point::Point(float x, float y, float velocityX, float velocityY) :
    Point(x, y) {
    lastPosition.x -= velocityX;
    lastPosition.y -= velocityY;
}

// Returns the current position of the point.
const sf::Vector2f &Point::getPosition() const {
    return position;
}

// Updates the position and velocity of the point using Verlet Integration.
void Point::update() {
    // Do not move if the point should not move.
    if (staticPoint) {
        return;
    }

    // Find the velocity of the point.
    float velocityX = (position.x - lastPosition.x) * FRICTION;
    float velocityY = (position.y - lastPosition.y) * FRICTION;

    // Store the current position.
    lastPosition.x = position.x;
    lastPosition.y = position.y;

    // Move the point by the velocity found earlier and add gravity.
    position.x += velocityX;
    position.y += velocityY + GRAVITY;

    // Keep the point within the boundaries of the screen.
    constrain();
}

// Sets whether or not the point is stuck.
void Point::setStatic(bool isStatic) {
    staticPoint = isStatic;
}

// Keeps the point within the boundaries of the screen by having the point
// bounce off any boundaries it encounters.
void Point::constrain() {
    // Do not constraint points that do not move.
    if (staticPoint) {
        return;
    }

    // Find the velocity of the point.
    float velocityX = (position.x - lastPosition.x) * FRICTION;
    float velocityY = (position.y - lastPosition.y) * FRICTION;

    // Bounce off side walls.
    if (position.x > (640.0f - POINT_RADIUS)) {
        position.x = 640.0f - POINT_RADIUS;
        lastPosition.x += velocityX * BOUNCINESS;
    } else if (position.x < POINT_RADIUS) {
        position.x = POINT_RADIUS;
        lastPosition.x += velocityX * BOUNCINESS;
    }

    // Bounce off the ceiling and floor.
    if (position.y > (480.0f - POINT_RADIUS)) {
        position.y = 480.0f - POINT_RADIUS;
        lastPosition.y += velocityY * BOUNCINESS;
    } else if (position.y < POINT_RADIUS) {
        position.y = POINT_RADIUS;
        lastPosition.y += velocityY * BOUNCINESS;
    }
}

// Returns the distance between this point and another point squared by
// using the distance formula.
float Point::distSqr(const Point &other) {
    const sf::Vector2f &otherPos = other.getPosition();

    return (position.x - otherPos.x) * (position.x - otherPos.x) +
        (position.y - otherPos.y) * (position.y - otherPos.y);
}

// Changes the position of the point by a given amount. If force is specified,
// then the point will move regardless if the point is static.
void Point::move(float deltaX, float deltaY, bool force) {
    // Do not move if the point should not move.
    if (!force && staticPoint) {
        return;
    }

    position.x += deltaX;
    position.y += deltaY;
}

// Sets the position of the point to the given position.
void Point::setPosition(const sf::Vector2f &newPosition) {
    position = newPosition;
    lastPosition = newPosition;
}