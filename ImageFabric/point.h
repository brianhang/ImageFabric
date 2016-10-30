#pragma once

#include <SFML/Graphics.hpp>

// A point on the cloth that is simulated using Verlet Integration.
class Point {
    private:
        // The current position of the point.
        sf::Vector2f position;

        // The position of the point in the previous frame.
        sf::Vector2f lastPosition;

        // Whether or not the point is simulated.
        bool staticPoint;

    public:
        // Constructors for the point.
        Point();
        Point(float x, float y);
        Point(float x, float y, float velocityX, float velocityY);

        // Returns the position of this point as a vector.
        const sf::Vector2f &getPosition() const;

        // Performs one step of the physics simulation for this point.
        void update();

        // Moves the point by a given amount.
        void move(float deltaX, float deltaY, bool force = false);

        // Constrains the point to the boundaries of the screen.
        void constrain();

        // Sets whether or not the point should stay still.
        void setStatic(bool isStatic);

        // Sets the position of the point.
        void setPosition(const sf::Vector2f &newPosition);

        // Returns the distance squared from this point to another point.
        float distSqr(const Point &other);
};