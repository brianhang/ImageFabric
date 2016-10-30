 #include "stick.h"

// Constructor for the Stick class. Assigns the start and end points and sets
// the desired distance to the initial distance between the two points.
Stick::Stick(Point *newStart, Point *newEnd) : start(newStart), end(newEnd) {
    length = start->distSqr(*newEnd);
}

// Moves the endpoints of the stick towards/away from each other to maintain
// the desired length.
void Stick::constrain() {
    const sf::Vector2f &startPos = start->getPosition();
    const sf::Vector2f &endPos = end->getPosition();

    // Calculate the slope of the two points.
    float deltaX = startPos.x - endPos.x;
    float deltaY = startPos.y - endPos.y;

    // Get how far away the length is from the desired length.
    float deltaLength = (deltaX * deltaX) + (deltaY * deltaY);
    float scale = (sqrt(length / deltaLength) - 1.0f) / 4.0f;

    // Find how much to move the points to get them to the right length.
    float offsetX = deltaX * scale;
    float offsetY = deltaY * scale;

    start->move(offsetX, offsetY);
    end->move(-offsetX, -offsetY);
}