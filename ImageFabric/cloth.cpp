#include "cloth.h"

// Number of iterations per frame for constraining points.
#define ITERATIONS 10

// Number of points in 2 triangles to draw a quad.
#define TRIANGLES 6

Cloth::Cloth(unsigned int newWidth, unsigned int newHeight, float newSpacing) :
width(newWidth), height(newHeight), spacing(newSpacing) {
    // The previous point created.
    Point *left = nullptr;

    // Create a rectangular grid of points.
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            // Create the point object.
            Point *point = new Point(x * spacing, y * spacing);

            // Attach the point to the point above it.
            if (y > 0) {
                Point *above = getPoint(x, y - 1);

                sticks.push_back(new Stick(above, point));
            }

            // Attach the point to the point on the left.
            if (x > 0) {
                sticks.push_back(new Stick(left, point));
            }

            // Add the point to the list of points in the fabric.
            points.push_back(point);

            // Store the "left" point for the next point.
            left = point;
        }
    }

    // Set up the vertices for the cloth.
    vertices.setPrimitiveType(sf::Triangles);
    vertices.resize(points.size() * TRIANGLES);

    transformX = 0.0f;
    transformY = 0.0f;
}

Cloth::~Cloth() {
    for (unsigned int i = 0; i < points.size(); i++) {
        delete points[i];
    }

    points.clear();
}

void Cloth::update() {
    unsigned int i;

    // Move every point.
    for (i = 0; i < points.size(); i++) {
        points[i]->update();
    }

    // Maintain constraints between points.
    for (i = 0; i < sticks.size(); i++) {
        for (unsigned int j = 0; j < ITERATIONS; j++) {
            sticks[i]->constrain();
        }
    }
}

void Cloth::draw(sf::RenderWindow &window) {
    int i = 0;

    // Set up the vertices of the cloth polygon.
    for (unsigned int y = 0; y < width - 1; y++) {
        for (unsigned int x = 0; x < width - 1; x++) {
            vertices[i] = points[y * width + x]->getPosition();
            vertices[i].texCoords.x = (x * spacing) * transformX;
            vertices[i].texCoords.y = (y * spacing) * transformY;

            vertices[++i] = points[(y + 1) * width + x]->getPosition();
            vertices[i].texCoords.x = (x * spacing) * transformX;
            vertices[i].texCoords.y = ((y + 1) * spacing) * transformY;

            vertices[++i] = points[(y + 1) * width + x + 1]->getPosition();
            vertices[i].texCoords.x = ((x + 1) * spacing) * transformX;
            vertices[i].texCoords.y = ((y + 1) * spacing) * transformY;

            vertices[++i] = points[y * width + x]->getPosition();
            vertices[i].texCoords.x = (x * spacing) * transformX;
            vertices[i].texCoords.y = (y * spacing) * transformY;

            vertices[++i] = points[y * width + x + 1]->getPosition();
            vertices[i].texCoords.x = ((x + 1) * spacing) * transformX;
            vertices[i].texCoords.y = (y * spacing) * transformY;

            vertices[++i] = points[(y + 1) * width + x + 1]->getPosition();
            vertices[i].texCoords.x = ((x + 1) * spacing) * transformX;
            vertices[i].texCoords.y = ((y + 1) * spacing) * transformY;

            i++;
        }
    }

    window.draw(vertices, renderState);
}

void Cloth::setTexture(const sf::Texture &texture) {
    // Get the size of the texture.
    sf::Vector2u size = texture.getSize();

    // Create a ratio for a point relative to the cloth to a point
    // on the texture.
    transformX = size.x / (width * spacing);
    transformY = size.y / (height * spacing);

    // Apply the actual texture.
    renderState.texture = &texture;
}

Point *Cloth::getPoint(unsigned int x, unsigned int y) {
    return points[y * width + x];
}